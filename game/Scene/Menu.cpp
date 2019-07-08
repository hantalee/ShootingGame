#include "Menu.h"

#include "Loading.h"
#include "Stage.h"

#include "MenuBtn.h"
#include "OptionBtn.h"

Texture* menuBG;
Texture* tempMenu;

void loadMenu()
{
	setStringSize(30);
	setStringRGBA(RGBA_GREEN);
	setStringBorder(5);
	setStringBorderRGBA(RGBA_BLACK);
	const char* str = "MENU";
	iGraphics* g = iGraphics::share();
	iSize size = sizeOfString(str);
	g->init(size);

	g->drawString(0, 0, TOP|LEFT, str);

	tempMenu = g->getTexture();

	createMenuBtn();
}

void freeMenu()
{
	if(menuBG)
		freeImage(menuBG);

	freeMenuBtn();
}

void drawMenu(float dt)
{
	setRGBA(1, 1, 1, 1);
	fillRect(iRectMake(0, 0, devSize.width, devSize.height));

	drawImage(tempMenu, tempMenu->width, tempMenu->height, VCENTER|HCENTER);

	drawMenuBtn(dt);
}

void keyMenu(iKeyState stat, iPoint point)
{
	if( keyMenuBtn(stat, point) )
	{
		return;
	}
}








