#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "glut.h"
#include "font.h"
#include "Rect.h"
#include <time.h>
#include "audio.h"
#include "Rect.h"
#include "tex.h"
#include "Header.h"



using namespace glm;
#define BALL_MAX 2

bool g_keys[256];

Player g_player;
PlayerExplosion g_playerExplosion;
PlayerBullet g_playerBullet;
Explosion g_playerBulletExplosion;
Explosion g_invaderExplosion;
Explosion g_invaderBulletExplosions[INVADER_BULLET_MAX];
Ground g_ground;
Pillbox g_Pillboxes[PILLBOX_MAX];

void setColorWithPosition(vec2 const& position) {
	if (position.y < 8 * 6)
		glColor3ub(0xff, 0x00, 0x00);
	else if	
		(position.y < 8 * 20)
		glColor3ub(0xff, 0xff, 0xff);
	else
		glColor3ub(0x00, 0xff, 0x00);
}
void display() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);//(GLenum mode);
	glLoadIdentity();
	gluOrtho2D(
		0,//GLdouble left,
		SCREEN_WIDTH,//GLdouble right,
		SCREEN_HEIGHT,	//GLdouble bottom,
		0);	//GLdouble top);
	glMatrixMode(GL_MODELVIEW);//GLenum mode
	glLoadIdentity();
	
	glEnable(GL_TEXTURE_2D);  //GLenum cap);
	glEnable(GL_BLEND);
	glBlendFunc(
		GL_SRC_ALPHA,//(GLenum sfactor,
		GL_ONE_MINUS_DST_ALPHA);//GLenum dfactor);
	
	//Rect(vec2(128, 128)).draw();
	g_ground.draw();
	for (int i = 0; i < PILLBOX_MAX; i++)
		g_Pillboxes[i].draw();
	InvaderBullet::drawAll();
	Invader::drawAll();
	for (int i = 0; i < INVADER_BULLET_MAX; i++)
		g_invaderBulletExplosions[i].draw();
	g_invaderExplosion.draw();
	g_playerBulletExplosion.draw();
	g_playerBullet.draw();
	g_player.draw();
	g_playerExplosion.draw();

	fontBegin();
	fontHeight(FONT_DEFAULT_HEIGHT);
	fontWeight(fontGetWeightMax());
	fontFont(FONT_FONT_ROMAN);
	fontPosition(0,0);
	glColor3ub(0xff, 0xff, 0xff);
	fontEnd();

	glutSwapBuffers();
};

void idle(void){
	audioUpdate();
	for (int i = 0; i < INVADER_BULLET_MAX; i++)
		g_invaderBulletExplosions[i].update();
	InvaderBullet::updateAll();
	g_invaderExplosion.update();
	Invader::updateAll();
	g_playerBulletExplosion.update();
	g_playerExplosion.update();
	g_player.update();
	g_playerBullet.update();
	glutPostRedisplay();
	
}
void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
}
void reshape(int width, int height) {
	printf("rehape:width:%d height:%d\n",width,height);
	glViewport(0,0,width,height);
	//GLint x, GLint y, GLsizei width, GLsizei height);
	}
void keyboard(unsigned char key, int x, int y) {
	if (key == 0x1b)
		exit(0);
	//printf("keyboard:\'%c\'(%#x)\n", key, key);
	g_keys[key] = true;

	switch (key) {
	case ' ':g_player.shoot();
		break;
	}
	
}
void keyboardUp(unsigned char key, int x, int y) {
	//printf("keyboardUp:\'%c\'(%#x)\n", key, key);
	g_keys[key] = false;
}
void passiveMotion(int x, int y) {
	//printf("passoveMotion::x:%d y:%d\n",x,y);
}
int main(int argc, char* argv[]) {
	srand(time(NULL));
	audioInit();
	glutInit(&argc, argv);

	glutInitDisplayMode(GL_DOUBLE);
	glutInitWindowPosition(640,0);
	{
		int height = 720;
		int width = 720*4/3;
		glutInitWindowSize(width, height);
	}
	glutCreateWindow("tittle");

	g_player.init();
	g_playerExplosion.init();
	g_playerBullet.init();
	g_playerBulletExplosion.init("textures\\player_bullet_explosion.bmp",
		vec2(8,8));
	g_invaderExplosion.init("textures\\invader_explosion.bmp",vec2(13, 8));
	g_invaderBulletExplosions[0].init("textures\\invader_bullet_explosion.bmp", vec2(8, 8));
	g_invaderBulletExplosions[1] = g_invaderBulletExplosions[0];
	Invader::initAll();
	InvaderBullet::initAll();
	g_ground.init();
	{
		int x = (SCREEN_WIDTH - PILLBOX_WIDTH * (PILLBOX_MAX * 2 - 1))/2;
		for (int i = 0; i < PILLBOX_MAX; i++) {
			g_Pillboxes[i].init();
			g_Pillboxes[i].m_position = vec2(
			x, PILLBOX_TOP);
			x += PILLBOX_WIDTH * 2;
		}
	}
	glutDisplayFunc(display);
	//glutTimerFunc(0, timer, 0);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);//void (GLUTCALLBACK *func)(int width, int height));
	glutKeyboardFunc(keyboard);//GLUTCALLBACK *func)(unsigned char key, int x, int y));
	glutKeyboardUpFunc(keyboardUp);//void (GLUTCALLBACK *func)(unsigned char key, int x, int y));
	//glutPassiveMotionFunc(passiveMotion); //void (GLUTCALLBACK * func)(int x, int y));
    //glutMotionFunc(motion); void (GLUTCALLBACK * func)(int x, int y));
	glutIgnoreKeyRepeat(GL_TRUE);//int ignore
	glutPassiveMotionFunc(passiveMotion);//void (GLUTCALLBACK *func)(int x, int y));
	glutMainLoop();
}