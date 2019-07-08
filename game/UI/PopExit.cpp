#include "PopExit.h"


iPopup* popExit = NULL;
iImage** imgExitBtn;

void createPopExit()
{
	iImage* img;
	Texture* tex;
	int i, j;

	iPopup* pop = new iPopup(iPopupStyleZoom);

	iGraphics* g = iGraphics::share();
	iSize size = iSizeMake(400, 200);// 팝업사이즈
	{
		g->init(size);

		setRGBA(RGB_BLACK,0.5);
		g->fillRect(0, 0, size.width, size.height, 10);

		tex = g->getTexture();
		img = new iImage();
		img->addObject(tex);
		freeImage(tex);
		pop->addObject(img);
	}

	const char* strBtn[2] = {"EXIT", "CANCEL"};// 80x40
	imgExitBtn = (iImage**)malloc(sizeof(iImage*)*2);
	iSize sizeBtn = iSizeMake(100, 50);
	int a = (size.width-sizeBtn.width*2)/3;
	for(i=0; i<2; i++)
	{
		img = new iImage();
		for(j=0; j<2; j++)
		{
			g->init(sizeBtn);

			setRGBA(RGBA_WHITE);
			g->fillRect(0, 0, sizeBtn.width, sizeBtn.height, 6);

			setStringSize(30);
			setStringBorder(3);
			if( j==0 )	setStringRGBA(RGBA_BLACK);
			else		setStringRGBA(RGBA_RED);
			setStringBorderRGBA(RGBA_YELLOW);
			g->drawString(sizeBtn.width/2, sizeBtn.height/2, VCENTER|HCENTER, strBtn[i]);

			tex = g->getTexture();
			img->addObject(tex);
			freeImage(tex);
		}
		img->position = iPointMake(a + (sizeBtn.width+a)*i, (size.height-sizeBtn.height)/2);
		pop->addObject(img);
		imgExitBtn[i] = img;
	}

	pop->methodPaintBefore = drawPopExitBefore;
	pop->setup( iPointMake(devSize.width/2, devSize.height/2),
				iPointMake(	(devSize.width-size.width)/2,
							(devSize.height-size.height)/2));
	popExit = pop;
}

void freePopExit()
{
	delete popExit;
	free( imgExitBtn );
}

void showPopExit(bool show)
{
	popExit->show(show);
	if( show )
	{

	}
}

void drawPopExitBefore(void* parm, iPoint point, float scale, float alpha, float dt)
{
	for(int i=0; i<2; i++)
		imgExitBtn[i]->setTexAtIndex(popExit->selected==i);
}

void drawPopExit(float dt)
{
	popExit->paint(dt);
}

bool keyPopExit(iKeyState stat, iPoint point)
{
	if( popExit->bShow==false )
		return false;
	//if( popExit->stat==iPopupStatOpen || popExit->stat==iPopupStatClose )
	if( popExit->stat!=iPopupStatProc )
		return true;

	int i, j = -1;

	switch( stat ) {

	case iKeyStateBegan:
		if( popExit->selected==-1 ) break;
		if( popExit->selected==0 )
		{
			// yes 게임죵료
			void exitProgram();
			exitProgram();
		}
//		else// if( popExit->selected==1 )
//		{
//		}
		showPopExit(false);
//		audioPlay(snd_btn);
		break;

	case iKeyStateMoved:
		for(i=0; i<2; i++)
		{
			if( containPoint(point, imgExitBtn[i]->touchRect(popExit->closePoint)) )
			{
				j = i;
				break;
			}
		}
//		if( popExit->selected!=j )
//			audioPlay(snd_btn);
		popExit->selected = j;
		break;

	case iKeyStateEnded:
		break;

	default:
		break;
	}

	return true;
}
