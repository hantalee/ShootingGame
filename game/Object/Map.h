#pragma once

#include "iStd.h"

#define SCROLL_SPEED 10

class Map;
extern Map* map;

class Map
{
public:
	Texture* mapTex;
	iPoint off;
	iSize size;
public:
	void paint(float dt);
public:
	Map();
	virtual ~Map();
};
