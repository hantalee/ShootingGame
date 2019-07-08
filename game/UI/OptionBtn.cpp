#include "OptionBtn.h"



iPopup* popOption = NULL;
iImage** imgOptionBtn;

const char* optionStr[2] = {"SAVE","CANCEL"};

void createOptionPop()
{
	int i,j;

	Texture* tex;
	iImage* img;

	iPopup* pop = new iPopup(iPopupStyleZoom);

	iGraphics* g = iGraphics::share();

	iSize optionSize = iSizeMake(1000,1000);
	{
		g->init(optionSize);

		setRGBA(RGB_BLACK, 0.5);
		g->fillRect(0,0,optionSize.width,optionSize.height,10);
		setRGBA(RGB_BLACK, 1);

		tex = g->getTexture();
		img = new iImage();
		img->addObject(tex);
		freeImage(tex);
		pop->addObject(img);
	}

	imgOptionBtn = (iImage**)malloc(sizeof(iImage*)*2);
	iSize btnSize = iSizeMake(130,50);
	{
		for(i=0; i<2; i++)
		{
			img = new iImage();
			for(j=0; j<2; j++)
			{
				g->init(btnSize);

				setRGBA(RGBA_WHITE);
				g->fillRect(0,0,btnSize.width,btnSize.height,10);

				setStringSize(40);
				if(j==0)		setStringRGBA(RGBA_BLACK);
				else 			setStringRGBA(RGBA_RED);
				setStringBorder(3);
				setStringBorderRGBA(RGBA_YELLOW);
				g->drawString(btnSize.width/2, btnSize.height/2, VCENTER|HCENTER, optionStr[i]);

				tex = g->getTexture();
				img->addObject(tex);
				freeImage(tex);
			}
			int a = (optionSize.width-btnSize.width*2)/3;
			img->position = iPointMake((i+1)*a + (btnSize.width*i),
										(optionSize.height-100));

			pop->addObject(img);
			imgOptionBtn[i] = img;
		}

	}
	pop->methodPaintBefore = drawPopOptionBtnBefore;
	pop->setup(iPointMake(devSize.width/2, devSize.height/2),
				iPointMake(devSize.width/2-optionSize.width/2, devSize.height/2-optionSize.height/2));


	popOption = pop;
}

void freeOptionPop()
{
	delete popOption;
	free(imgOptionBtn);
}

void drawOptionPop(float dt)
{
	popOption->paint(dt);
}

void drawPopOptionBtnBefore(void* parm, iPoint point, float scale, float alpha, float dt)
{
	for(int i=0; i<2; i++)
		imgOptionBtn[i]->setTexAtIndex(popOption->selected==i);
}

bool keyOptionPop(iKeyState stat, iPoint point)
{
	if(popOption->bShow==false)
			return false;

	if(popOption->stat!=iPopupStatProc)
		return true;

	int i, j=-1;

	switch(stat)
	{
	case iKeyStateBegan:
	{
		if(popOption->selected==-1) break;
		if(popOption->selected==0)
		{
			//save
		}
		else if(popOption->selected==1)
		{
			popOption->show(false);
		}
		break;
	}
	case iKeyStateMoved:
	{
		for(i=0; i<2; i++)
		{
			if(containPoint(point, imgOptionBtn[i]->touchRect(popOption->closePoint)))
			{
				j = i;
				break;
			}
		}
		popOption->selected = j;
		break;
	}
	case iKeyStateEnded:
		break;
	default:
		break;
	}

	return true;
}
