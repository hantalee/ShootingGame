#include "Enemy.h"


igImage** enemyTexList;

Enemy** enemy;
Enemy** _enemy;
int enemyNum, _enemyNum;

void methodAI_Nomal(Enemy* e, iPoint pos, float dt);
void methodAI_Fast(Enemy* e, iPoint pos, float dt);
METHOD_ENEMY_AI aiMethod[ENEMY_TYPE_NUM] = {
		methodAI_Nomal, methodAI_Fast
};


bool Enemy::paint(float dt, iPoint off)
{
	iPoint p = position + off;
	methodAI(this, p, dt);

	return false;
}

void loadEnemy(EnemyList* enemyList)
{
	int i;

	loadEnmeyTex();

	for(i=0; i<ENEMY_NUM; i++)
	{
		if(enemyList[i].index == EnemyType_none)
			break;
	}
	enemyNum = _enemyNum = i;

	_enemy = (Enemy**)malloc(sizeof(Enemy*)*_enemyNum);
	enemy = (Enemy**)malloc(sizeof(Enemy*)*_enemyNum);
	for(i=0; i<_enemyNum; i++)
	{
		Enemy* e = new Enemy();
		e->active = false;
		e->position = enemyList[i].position;
		e->methodAI = aiMethod[enemyList[i].index];
		e->tex = (Texture*)enemyTexList[enemyList[i].index];

		_enemy[i] = enemy[i] = e;
	}
}
void freeEnemy()
{
	for(int i=0; i<_enemyNum; i++)
		delete _enemy[i];
	free(_enemy);
	free(enemy);

	for(int i=0; i<ENEMY_TYPE_NUM; i++)
		free(enemyTexList[i]);
	free(enemyTexList);
}
void drawEnemy(float dt, iPoint off)
{
	for(int i=0; i<enemyNum; i++)
	{
		if(enemy[i]->paint(dt, off))
		{
			enemyNum--;
			for(int j=i; j<enemyNum; j++)
				enemy[j] = enemy[1+j];
			i--;
		}
	}
}

void methodAI_Nomal(Enemy* e, iPoint pos, float dt)
{
	drawImage(e->tex, pos.x, pos.y, e->tex->width, e->tex->height, VCENTER|HCENTER);

	e->position.y += 300*dt;
}
void methodAI_Fast(Enemy* e, iPoint pos, float dt)
{
	drawImage(e->tex, pos.x, pos.y, e->tex->width, e->tex->height, VCENTER|HCENTER);

	e->position.y += 700*dt;
}

void loadEnmeyTex()
{
	enemyTexList = (igImage**)calloc(sizeof(igImage*), ENEMY_TEX_NUM);
#if 0
	iGraphics* g = iGraphics::share();
	igImage* temp;
	iSize texSize;
	for(int i=0; i<ENEMY_TEX_NUM; i++)
	{
		if(i==EnemyType_nomal)
		{
			temp = g->createIgImage("assets/Enemy/enemyBlack1.PNG");
			texSize = iSizeMake(g->getIgImageWidth(temp),g->getIgImageHeight(temp));
		}
		else if(i==EnemyType_Fast)
		{
			temp = g->createIgImage("assets/Enemy/enemyRed5.PNG");
			texSize = iSizeMake(g->getIgImageWidth(temp),g->getIgImageHeight(temp));
		}

		g->init(texSize);

		g->drawIgImage(	temp, texSize.width/2, texSize.height/2,
						texSize.width, texSize.height, VCENTER|HCENTER);
		g->freeIgImage(temp);

		enemyTexList[i] = g->getTexture();


	}
#else
	const char* strPath[2] = {
		"assets/Enemy/enemyBlack1.PNG",
		"assets/Enemy/enemyRed5.PNG"
	};

	for(int i=0; i<ENEMY_TEX_NUM; i++)
		enemyTexList[i] = createImage(strPath[i]);
#endif
}



