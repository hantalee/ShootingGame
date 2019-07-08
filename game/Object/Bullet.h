#pragma once

#include "iStd.h"

#define BULLET_TYPE_NUM 2
#define MAX_BULLET_NUM 100

#define nomalType 0
#define guidedType 1

struct Bullet;
typedef void (*METHOD_BULLET_TYPE)(float dt, iPoint pos, Bullet* obj);

struct Bullet
{
	bool alive;
	iPoint position, prevPos;
	iPoint vector;
	float degree;
	float dt;
	void* attker;
	METHOD_BULLET_TYPE typeMethod;

	bool paint(float dt, iPoint off);
	bool meet();
};

void loadBullet();
void freeBullet();
void drawBullet(float dt, iPoint off);
void addBullet(int index, void* attker, iPoint startPos, iPoint targetPos);

