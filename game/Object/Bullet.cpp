#include "Bullet.h"

#include "Map.h"


Texture* nomalTex;
Texture* guidedTex;

Bullet** _bullet;
Bullet** bullet;

int bulletNum;

void nomalBullet(float dt, iPoint pos, Bullet* obj);
void guidedBullet(float dt, iPoint pos, Bullet* obj);
METHOD_BULLET_TYPE methodType[BULLET_TYPE_NUM] =
{
		nomalBullet, guidedBullet
};


bool Bullet::paint(float dt, iPoint off)
{
	iPoint p = position + off;
	typeMethod(dt, p, this);

	p = position + map->off;
	if(	p.x < 0 ||
		p.x > devSize.width ||
		p.y < 0 ||
		p.y > devSize.height)
	{
		alive = false;
		return true;
	}


	return false;
}
bool Bullet::meet()
{
	return false;
}

void loadBullet()
{
	iGraphics* g = iGraphics::share();
	iSize bulletSize = iSizeMake(9, 54);
	{
		g->init(bulletSize);

		igImage* ig = g->createIgImage("assets/laserBlue01.PNG");
		g->drawIgImage(	ig, bulletSize.width/2, bulletSize.height/2,
						bulletSize.width, bulletSize.height, VCENTER|HCENTER);
		g->freeIgImage(ig);
	}
	nomalTex = g->getTexture();

	_bullet = (Bullet**)calloc(sizeof(Bullet*), BULLET_TYPE_NUM);
	for(int i=0; i<BULLET_TYPE_NUM; i++)
	{
		_bullet[i] = (Bullet*)calloc(sizeof(Bullet), MAX_BULLET_NUM);
		for(int j=0; j<MAX_BULLET_NUM; j++)
			_bullet[i][j].typeMethod = methodType[i];
	}

	bullet = (Bullet**)calloc(sizeof(Bullet*), MAX_BULLET_NUM*BULLET_TYPE_NUM);
	bulletNum = 0;
}
void freeBullet()
{
	free(nomalTex);

	for(int i=0; i<BULLET_TYPE_NUM; i++)
		free(_bullet[i]);
	free(_bullet);
	free(bullet);
}
void drawBullet(float dt, iPoint off)
{
	for(int i=0; i<bulletNum; i++)
	{
		if(bullet[i]->paint(dt, off))
		{
			bulletNum--;
			for(int j=i; j<bulletNum; j++)
				bullet[j] = bullet[j+1];
			i--;
		}
	}
}

void addBullet(int index, void* attker, iPoint startPos, iPoint targetPos)
{
	for(int i=0; i<MAX_BULLET_NUM; i++)
	{
		Bullet* b = &_bullet[index][i];
		if(b->alive == false)
		{
			b->alive = true;
			b->position = startPos;
			iPoint v = targetPos - startPos;
			b->vector = v / iPointLength(v);
			b->degree = 360 - iPointAngle(iPointMake(1,0), iPointZero, v);
			b->prevPos = startPos;
			b->dt = 0.0f;
			b->attker = attker;

			bullet[bulletNum] = b;
			bulletNum++;
			return;
		}
	}
}

void nomalBullet(float dt, iPoint pos, Bullet* obj)
{
	drawImage(nomalTex, pos.x, pos.y, nomalTex->width,nomalTex->height, VCENTER|HCENTER);

	obj->position += obj->vector * (1000*dt);
}
void guidedBullet(float dt, iPoint pos, Bullet* obj)
{

}




