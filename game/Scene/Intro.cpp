#include "Intro.h"

#include "Menu.h"
#include "Loading.h"


Texture* introBG;
Texture* introStr;

float introDt;

void loadIntro()
{
//	introBG = createImage("assets/iu.jpg");

	introDt = 0.0000001;

	setStringSize(30);
	setStringRGBA(RGBA_GREEN);
	setStringBorder(5);
	setStringBorderRGBA(RGBA_BLACK);
	const char* str = "INTRO";
	iSize size = sizeOfString(str);
	iGraphics* g = iGraphics::share();
	g->init(size);

	g->drawString(0, 0, TOP|LEFT, str);

	introStr = g->getTexture();
}

void freeIntro()
{
	if(introBG)
		freeImage(introBG);
}

void drawIntro(float dt)
{
	setRGBA(1, 1, 1, 1);
	fillRect(iRectMake(0, 0, devSize.width, devSize.height));

//	if(introBG)
//	{
//		drawImage(introBG, devSize.width/2, devSize.height/2, VCENTER|HCENTER);
//	}

	drawImage(introStr, introStr->width, introStr->height, VCENTER|HCENTER);
}

void keyIntro(iKeyState stat, iPoint point)
{
	if( stat==iKeyStateBegan )
		setLoading(g_menu, freeIntro, loadMenu);
}
