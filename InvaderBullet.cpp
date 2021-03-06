#include "InvaderBullet.h"
#include "glut.h"
#include "Header.h"
#include "tex.h"

InvaderBullet g_invaderBullets[INVADER_BULLET_MAX];

static GLuint textures[INVADER_BULLET_ANIMATION_TYPE_MAX][INVADER_BULLET_ANIMATION_LENGTH];
int InvaderBullet::init() {
	m_size=vec2(INVADER_BULLET_WIDTH, INVADER_BULLET_HEIGHT);
		return 0; 
}
int InvaderBullet::initAll() {
	glGenTextures(
		INVADER_BULLET_ANIMATION_TYPE_MAX* INVADER_BULLET_ANIMATION_LENGTH,          //GLsizei n, 
		*textures);//GLuint *textures);
	
	{
		char fileName[256];
		for (int i = 0; i < INVADER_BULLET_ANIMATION_TYPE_MAX; i++) {
			for (int j = 0; j < INVADER_BULLET_ANIMATION_LENGTH; j++) {
				sprintf_s(fileName,sizeof(fileName), "textures\\invader_bullet%d-%d.bmp", i, j);
				glBindTexture(
					GL_TEXTURE_2D, //GLenum target, 
					textures[i][j]);       //GLuint texture)
				texFromBPM(fileName, 0x00, 0xff, 0x00);
			}
		}
	}
	for (int i = 0; i < INVADER_BULLET_MAX; i++)
		g_invaderBullets[i].init();
	return 0;
}
void InvaderBullet::update() {
	if (!m_enable)
		return;
	m_position.y += INVADER_BULLET_SPEED;

	if (
		(g_playerExplosion.m_countLeft<=0)
		&& g_player.intersect(m_position + vec2((int)m_size.x / 2, m_size.y)) )
	{
		g_playerExplosion.start(
			vec2(g_player.m_position.x,
				g_player.m_position.y));
		g_player.m_position.x = PLAYER_DEFAULT_X;
		m_enable = false;
		return;
	}
	

	if (m_position.y >= SCREEN_HEIGHT - 8 - m_size.y) {
		m_enable = false;
		for (int i = 0; i < INVADER_BULLET_MAX; i++) {
			Explosion *pExplosion = &g_invaderBulletExplosions[i];
			if (pExplosion->m_countLeft <= 0) {
				pExplosion->start(
					vec2(
						m_position.x - (pExplosion->m_size.x - m_size.x) / 2.f,
						m_position.y
					)
				);
				break;
			}
		}
		{
			int x = m_position.x + (int)(m_size.x / 2);
			
			for (int i=x-2;i<=x+2;i+=2)
				g_ground.erasePixel(i);
			}
		return;
		}
	if (m_animationWait > 0)
		m_animationWait--;
	else {
		++m_animationFrame %= INVADER_BULLET_ANIMATION_LENGTH;
		m_animationWait = INVADER_BULLET_ANIMATION_WAIT_MAX;
	}
}
void InvaderBullet::updateAll() {
	for (int i = 0; i < INVADER_BULLET_MAX; i++)
		g_invaderBullets[i].update();
}
void InvaderBullet::draw() {
	if (!m_enable)
		return;
	
	glBindTexture(
		GL_TEXTURE_2D, //GLenum target, 
		textures[m_animationType][m_animationFrame]);

	setColorWithPosition(m_position);
	Rect::draw();
	
}
void InvaderBullet::drawAll() {
	for (int i = 0; i < INVADER_BULLET_MAX; i++)
		g_invaderBullets[i].draw();
}
void InvaderBullet::shoot(vec2 const& _position, Invader *_pOwner) {
	m_position = _position;
	m_enable = true;
	m_pOwner = _pOwner;

	m_animationType = rand() % INVADER_BULLET_ANIMATION_TYPE_MAX;

	
	m_animationWait = INVADER_BULLET_ANIMATION_WAIT_MAX;

}
int InvaderBullet:: getShootingCount() {
	int n = 0;
	for (int i = 0; i < INVADER_BULLET_MAX; i++)
		if (g_invaderBullets[i].m_enable)
			n++;
	return n;
}