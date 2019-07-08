#pragma once

#include "iStd.h"


class Player
{
public:
	Texture* playerTex;
	iPoint position;
	float moveSpeed;
public:
	void paint(float dt, iPoint off, bool ctrl);
public:
	Player();
	virtual ~Player();
};
