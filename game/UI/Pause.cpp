#include "Pause.h"

#include "Loading.h"
#include "Menu.h"
#include "Stage.h"

#include "OptionBtn.h"
#include "PopExit.h"

iPopup* popPause = NULL;
iImage** pauseBtn;

void createPause()
{
	int i, j;

	Texture* tex;
	iImage* img;

	iPopup* pop = new iPopup(iPopupStyleNone);

	iGraphics* g = iGraphics::share();

	iSize popPauseSize = iSizeMake(400,600);
	{
		g->init(popPauseSize);

		setRGBA(RGBA_GRAY);
		g->fillRect(0,0,popPauseSize.width, popPauseSize.height, 10);

		tex = g->getTexture();
		img = new iImage();
		img->addObject(tex);
		freeImage(tex);
		pop->addObject(img);
	}
//	img->position = iPointMake(	(devSize.width-popPauseSize.width)/2,
//								(devSize.height-popPauseSize.height)/2);


	const char* pauseBtnStr[PS_BTN_NUM] = {"RESTART","MENU","OPTION","EXIT"};
	pauseBtn = (iImage**)malloc(sizeof(iImage*)*PS_BTN_NUM);
	iSize pauseBtnSize = iSizeMake(200,100);
	int a = (popPauseSize.height-pauseBtnSize.height*4)/5;
	{
		for(i=0; i<PS_BTN_NUM;i++)
		{
			img = new iImage();
			for(j=0;j<2;j++)
			{
				g->init(pauseBtnSize);

				setRGBA(RGBA_BLUE);
				g->fillRect(0,0,pauseBtnSize.width,pauseBtnSize.height,5);

				setStringSize(30);
				if(j==0) 	setStringRGBA(RGBA_BLACK);
				else		setStringRGBA(RGBA_RED);
				setStringBorder(5);
				setStringBorderRGBA(RGBA_YELLOW);
				g->drawString(pauseBtnSize.width/2, pauseBtnSize.height/2,
						VCENTER|HCENTER, pauseBtnStr[i]);

				tex = g->getTexture();
				img->addObject(tex);
				freeImage(tex);
			}
			img->position = iPointMake((popPauseSize.width-pauseBtnSize.width)/2,
										a*(i+1) + pauseBtnSize.height*i);
			pop->addObject(img);
			pauseBtn[i] = img;
		}
	}

	pop->methodPaintBefore = drawPauseBtnBefore;
	pop->setup(	iPointMake(devSize.width/2, devSize.height/2),
				iPointMake(	(devSize.width-popPauseSize.width)/2,
							(devSize.height-popPauseSize.height)/2));

	popPause = pop;
}
void freePause()
{
	delete popPause;
	free(pauseBtn);
}

void drawPauseBtnBefore(void* parm, iPoint point, float scale, float alpha, float dt)
{
	for(int i=0; i<PS_BTN_NUM; i++)
		pauseBtn[i]->setTexAtIndex(popPause->selected==i);

	if(getKeyDown()&keyboard_esc)
	{
		popPause->show(false);
	}
	else if(getKeyDown()&keyboard_top)
	{
		popPause->selected--;
		if( popPause->selected < 0 )
			popPause->selected = 3;
	}
	else if(getKeyDown()&keyboard_bottom)
	{
		popPause->selected++;
		if( popPause->selected > 3 )
			popPause->selected = 0;
	}
}

void drawPause(float dt)
{
	popPause->paint(dt);
}
bool keyPause(iKeyState stat, iPoint point)
{
	if(popPause->bShow==false)
		return false;

	if(popPause->stat!=iPopupStatProc)
		return false;

	int i,j = -1;

	switch(stat)
	{
	case iKeyStateBegan:
		if(popPause->selected==-1) break;
		if(popPause->selected==PS_RESTART)
		{
			setLoading(g_stage, freeStage, loadStage);
		}
		else if(popPause->selected==PS_MENU)
		{
			setLoading(g_menu, freeStage, loadMenu);
		}
		else if(popPause->selected==PS_OPTION)
		{
			popOption->show(true);
		}
		else if(popPause->selected==PS_EXIT)
		{
			popExit->show(true);
		}
		break;
	case iKeyStateMoved:
		for(i=0; i<4; i++)
		{
			if(containPoint(point, pauseBtn[i]->touchRect(popPause->closePoint)))
			{
				j = i;
				break;
			}
		}
		popPause->selected = j;
		break;
	case iKeyStateEnded:
		break;
	default:
		break;
	}

	return true;
}














