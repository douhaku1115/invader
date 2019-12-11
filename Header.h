#pragma once
#include "PlayerBullet.h"
#include "Player.h"
#include "PlayerExplosion.h"
#include "Explosion.h"
#include "Invader.h"
#include "InvaderBullet.h"
#include <stdio.h>
#include "Ground.h"

#define SCREEN_WIDTH  256
#define SCREEN_HEIGHT 256

void setColorWithPosition(vec2 const& position);
extern bool g_keys[256];
extern Player g_player;
extern PlayerExplosion g_PlayerExplosion;
extern PlayerBullet g_playerBullet;
extern Explosion g_playerBulletExplosion;
extern Explosion g_invaderExplosion;
extern Explosion g_invaderBulletExplosions[INVADER_BULLET_MAX];
extern Ground g_Ground;