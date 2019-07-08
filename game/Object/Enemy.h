#pragma once

#include "iStd.h"

#include "StageData.h"


#define ENEMY_TEX_NUM 2

struct Enemy;
typedef void (*METHOD_ENEMY_AI)(Enemy* e, iPoint pos, float dt);

struct Enemy
{
	Texture* tex;
	iPoint position;
	bool active;

	METHOD_ENEMY_AI methodAI;

	bool paint(float dt, iPoint off);
};

void loadEnemy(EnemyList* enemyList);
void freeEnemy();
void drawEnemy(float dt, iPoint off);

void loadEnmeyTex();
