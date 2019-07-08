#include "Stage.h"

#include "Loading.h"
#include "Menu.h"

#include "PopStage.h"
#include "Pause.h"

#include "StageData.h"

#include "Map.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"


Texture* tempStage;

Player* player;

void loadStage()
{
	int stage = 0;
	StageInfo* sInfo = &stageInfo[stage];

	map = new Map();
	player = new Player();
	float startPosY = map->size.height - devSize.height/2 + 200;
	player->position = iPointMake(devSize.width/2, startPosY);

	loadBullet();
	loadEnemy(sInfo->enemyList);

	createPopStage();
	createPause();

	setStringSize(30);
	setStringRGBA(RGBA_GREEN);
	setStringBorder(5);
	setStringBorderRGBA(RGBA_BLACK);
	const char* str = "STAGE";
	iGraphics* g = iGraphics::share();
	iSize size = sizeOfString(str);
	g->init(size);

	g->drawString(0,0,TOP|LEFT,str);

	tempStage = g->getTexture();
}

void freeStage()
{
	delete map;
	delete player;
	freeBullet();
	freeEnemy();

	freePopStage();
	freePause();
}

void drawStage(float dt)
{
	float _dt = dt;
	if( popPause->bShow )
		dt = 0.0f;

	stageCheckKey(dt);

	map->paint(dt);
	player->paint(dt, map->off, dt==0.0f ? false : true);

	float prevOff = map->off.y;
	map->off.y += SCROLL_SPEED * dt;
	if(map->off.y>0)
		map->off.y = 0.0f;
	player->position.y -= map->off.y - prevOff;

	drawBullet(dt, map->off);
	drawEnemy(dt, map->off);

	drawPopStage(dt);

	drawPause(_dt);
}

void keyStage(iKeyState stat, iPoint point)
{
	if(keyPause(stat, point))
		return;
}


float delayDT = 0.0f;
float delayDT2 = 0.0f;
void stageCheckKey(float dt)
{
	if( popPause->bShow==false)
	{
		if( getKeyDown()&keyboard_esc )
		{
			popPause->show(true);
			return;
		}

		if(getKeyStat()&keyboard_a)
		{
			delayDT += dt;
			delayDT2 += dt;

			if(delayDT > 0.2f)
			{
				iPoint tp = iPointMake(player->position.x, player->position.y-10);
				addBullet(nomalType, player ,player->position, tp);
				delayDT -= 0.2f;
			}
			if( delayDT2 > 0.6f )
			{
				iPoint sp = iPointMake(player->position.x-20, player->position.y);
				iPoint tp = iPointMake(player->position.x-20, player->position.y-10);
				addBullet(nomalType, player ,sp, tp);
				sp.x += 40;
				tp.x += 40;
				addBullet(nomalType, player ,sp, tp);
				delayDT2 -= 0.6f;
			}
		}
	}
}

