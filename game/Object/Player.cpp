#include "Player.h"

#include "Map.h"


Player::Player()
{
	iGraphics* g = iGraphics::share();
	iSize playerSize = iSizeMake(99*2/3,75*2/3);
	{
		g->init(playerSize);

		igImage* ig = g->createIgImage("assets/playerShip1_green.PNG");
		g->drawIgImage(	ig, playerSize.width/2, playerSize.height/2,
						playerSize.width, playerSize.height, VCENTER|HCENTER);
		g->freeIgImage(ig);
	}
	playerTex = g->getTexture();

	position = iPointMake(devSize.width/2, devSize.height-30);
	moveSpeed = 300;
}
Player::~Player()
{
	freeImage(playerTex);
}

void Player::paint(float dt, iPoint off, bool ctrl)
{
	iPoint p = position + off;
	drawImage(playerTex, p.x, p.y, VCENTER|HCENTER);

//	printf("px : %f  	py : %f\n", position.x, position.y);
//	printf("ix : %f  	iy : %f\n", p.x, p.y);

	if(ctrl == false)
		return;

	iPoint v = iPointZero;
	switch(getKeyStat()&keyboard_mask)
	{
	case keyboard_left:							v.x = -1;				break;
	case keyboard_left|keyboard_top:			v.x = -1; 	v.y = -1;	break;
	case keyboard_left|keyboard_bottom:			v.x = -1; 	v.y = 1;	break;
	case keyboard_right:						v.x = 1;				break;
	case keyboard_right|keyboard_top:			v.x = 1; 	v.y = -1;	break;
	case keyboard_right|keyboard_bottom:		v.x = 1; 	v.y = 1;	break;
	case keyboard_top:										v.y = -1;	break;
	case keyboard_bottom:									v.y = 1;	break;
	}
	if(v != iPointZero)
	{
		position += v/iPointLength(v) * (moveSpeed*dt);

		float px = playerTex->width/2;
		float py = playerTex->height/2;
		if(position.x < px)
			position.x = px;
		else if(position.x > devSize.width - px)
			position.x = devSize.width - px;

		float y = position.y + map->off.y;
		if(y < py)
			y = py;
		else if(y > devSize.height - py)
			y = devSize.height - py;
		position.y = y - map->off.y;
	}
}














