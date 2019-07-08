#include "Map.h"

Map* map;

Map::Map()
{
	iGraphics* g = iGraphics::share();
	iSize  mapSize = iSizeMake(devSize.width,1973*devSize.width/960);//(960,1973);
	{
		g->init(mapSize);

		igImage* ig = g->createIgImage("assets/BG.jpg");
		g->drawIgImage(ig, mapSize.width/2, mapSize.height/2, mapSize.width, mapSize.height, VCENTER|HCENTER);
		g->freeIgImage(ig);
	}
	mapTex = g->getTexture();

	size = mapSize;
	off.x = 0;
	off.y = devSize.height - mapSize.height;
}
Map::~Map()
{
	free(mapTex);
}

void Map::paint(float dt)
{
	drawImage(mapTex, off.x, off.y, TOP|LEFT);
}
