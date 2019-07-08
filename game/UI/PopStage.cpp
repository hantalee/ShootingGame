#include "PopStage.h"

iPopup* popStage;

void createPopStage()
{
	Texture* tex;
	iImage* img;

	iPopup* pop = new iPopup(iPopupStyleNone);

	iGraphics* g = iGraphics::share();

	iSize PopBG = iSizeMake(devSize.width, devSize.height);
	{
		g->init(PopBG);

		setRGBA(RGB_BLACK,0);
		g->fillRect(0,0,PopBG.width,PopBG.height,0);

		tex = g->getTexture();
		img = new iImage();
		img->addObject(tex);
		freeImage(tex);
		pop->addObject(img);
	}


	const char* str = "SCORE";
	iSize ScoreSize = sizeOfString(str);
	{
		g->init(ScoreSize*2);

		setRGBA(RGBA_BLUE);
		g->fillRect(0,0,ScoreSize.width*2,ScoreSize.height*2,0);

		setStringSize(50);
		setStringRGBA(RGBA_BLACK);
		setStringBorder(0);
		setStringBorderRGBA(0,0,0,0);
		g->drawString(ScoreSize.width,ScoreSize.height,VCENTER|HCENTER,str);

		tex = g->getTexture();
		img = new iImage();
		img->addObject(tex);
		freeImage(tex);
		img->position = iPointMake(PopBG.width/2-ScoreSize.width, 0);
		pop->addObject(img);
	}

	const char* str1 = "HIGHSCORE";
	iSize hScoreSize = sizeOfString(str1);
	{
		g->init(hScoreSize);

		setRGBA(RGBA_BLUE);
		g->fillRect(0,0,hScoreSize.width,hScoreSize.height,0);

		setStringSize(50);
		setStringRGBA(RGBA_BLACK);
		setStringBorder(0);
		setStringBorderRGBA(0,0,0,0);
		g->drawString(hScoreSize.width/2,hScoreSize.height/2,VCENTER|HCENTER,str1);

		tex = g->getTexture();
		img = new iImage();
		img->addObject(tex);
		freeImage(tex);
		img->position = iPointMake(PopBG.width/2-hScoreSize.width/2, PopBG.height-hScoreSize.height);
		pop->addObject(img);
	}

	pop->setup(iPointMake(0,0),iPointMake(0,0));
	pop->show(true);

	popStage = pop;
}

void freePopStage()
{
	delete popStage;
}

void drawPopStage(float dt)
{
	popStage->paint(dt);
}

bool keyPopStage(iKeyState stat, iPoint point)
{
	return true;
}
