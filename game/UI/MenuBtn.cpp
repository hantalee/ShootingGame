#include "MenuBtn.h"

#include "Loading.h"
#include "Menu.h"
#include "Stage.h"

#include "PopExit.h"
#include "OptionBtn.h"


iPopup* popMenuBtn;
iImage** imgMenuBtn;

void drawPopMenuBtnBefore(void* parm, iPoint point, float scale, float alpha, float dt);

const char* strBtn[MN_BTN_NUM] = {"START", "OPTION", "EXIT"};
void createMenuBtn()
{
	Texture* tex;
	iImage* img;
	iPopup* pop = new iPopup(iPopupStyleMove);

	int i, j;

	iGraphics* g = iGraphics::share();
	iSize popSize = iSizeMake(512,512);
	{
		g->init(popSize);

		setRGBA(RGBA_WHITE);
		g->fillRect(0, 0, popSize.width, popSize.height, 10);

		tex = g->getTexture();
		img = new iImage();
		img->addObject(tex);
		freeImage(tex);
		pop->addObject(img);
	}


	imgMenuBtn = (iImage**)malloc(sizeof(iImage*)*MN_BTN_NUM);
	iSize btnSize = iSizeMake(100,60);
	int a = (popSize.height-btnSize.height*3)/4;
	for(i=0; i<MN_BTN_NUM; i++)
	{
		img = new iImage();
		for(j=0; j<2; j++)
		{
			g->init(btnSize);

			setRGBA(RGB_WHITE,0);
			g->fillRect(0,0, btnSize.width, btnSize.height, 10);

			setStringSize(30);
			setStringBorder(5);
			if(j==0)	setStringRGBA(RGBA_BLACK);
			else		setStringRGBA(RGBA_RED);
			setStringBorderRGBA(RGBA_YELLOW);
			g->drawString(btnSize.width/2, btnSize.height/2, VCENTER|HCENTER, strBtn[i]);

			tex = g->getTexture();
			img->addObject(tex);
			freeImage(tex);
		}
		img->position = iPointMake((popSize.width-btnSize.width)/2,
									a + (btnSize.height+a)*i);
		pop->addObject(img);
		imgMenuBtn[i] = img;
	}

	pop->methodPaintBefore = drawPopMenuBtnBefore;
	pop->setup( iPointMake((devSize.width-popSize.width)/2, devSize.height),
				iPointMake(	(devSize.width-popSize.width)/2,
							(devSize.height-popSize.height)/2));
	pop->show(true);

	popMenuBtn = pop;
}

void freeMenuBtn()
{
	delete popMenuBtn;
	free( imgMenuBtn );
}

void drawMenuBtn(float dt)
{
	popMenuBtn->paint(dt);
}

void drawPopMenuBtnBefore(void* parm, iPoint point, float scale, float alpha, float dt)
{
	for(int i=0; i<3; i++)
		imgMenuBtn[i]->setTexAtIndex(popMenuBtn->selected==i);
}

bool keyMenuBtn(iKeyState stat, iPoint point)
{
	if(popMenuBtn->bShow==false)
		return false;

	if(popMenuBtn->stat!=iPopupStatProc)
		return true;

	int i, j=-1;

	switch(stat)
	{
	case iKeyStateBegan:
	{
		if(popMenuBtn->selected==-1) break;
		if(popMenuBtn->selected==MN_START)
		{
			setLoading(g_stage, freeMenu, loadStage);
		}
		else if(popMenuBtn->selected==MN_OPTION)
		{
			popOption->show(true);
		}
		else if(popMenuBtn->selected==MN_EXIT)
		{
			popExit->show(true);
		}
		break;
	}
	case iKeyStateMoved:
	{
		for(i=0; i<3; i++)
		{
			if(containPoint(point, imgMenuBtn[i]->touchRect(popMenuBtn->closePoint)))
			{
				j = i;
				break;
			}
		}
		popMenuBtn->selected = j;
		break;
	}
	case iKeyStateEnded:
		break;
	default:
		break;
	}

	return true;
}
