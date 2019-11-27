#pragma once
#include "PlayerBullet.h"
#include "Player.h"
#include "Explosion.h"
#include "Invader.h"
#include "InvaderBullet.h"
#include <stdio.h>
#define SCREEN_WIDTH  256
#define SCREEN_HEIGHT 256

extern bool g_keys[256];
extern Player g_player;
extern PlayerBullet g_playerBullet;
extern Explosion g_playerBulletExplosion;
extern Explosion g_invaderExplosion;