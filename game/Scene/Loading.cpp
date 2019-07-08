#include "Loading.h"

GameState gameState;

GameState toGameState;
LOADING_METHOD methodFree, methodLoad;
float loadingDt = 0.0f;

Texture* texLoading;

void freeLoading()
{
	freeImage( texLoading );
}

void setLoading(GameState gs, LOADING_METHOD _methodFree, LOADING_METHOD _methodLoad)
{
	toGameState = gs;
	methodFree = _methodFree;
	methodLoad = _methodLoad;
	loadingDt = 0.000001f;

	setStringSize(30);
	setStringRGBA(1, 1, 1, 1);
	setStringBorder(5);
	setStringBorderRGBA(1, 0, 1, 1);
	const char* str = "Loading";
	iSize size = sizeOfString(str);
	iGraphics* g = iGraphics::share();
	g->init(size);

	g->drawString(0, 0, TOP|LEFT, str);

	texLoading = g->getTexture();
}

void drawLoading(float dt)
{
	if( loadingDt==0.0f )
		return;

	if( loadingDt<0.5f )
	{
		// fade-out 암전처리
		setRGBA(0, 0, 0, loadingDt/0.5f);
		fillRect(iRectMake(0, 0, devSize.width, devSize.height));
		setRGBA(1, 1, 1, 1);

		loadingDt += dt;
		if( loadingDt>=0.5f )
		{
			methodFree();

			gameState = toGameState;
			methodLoad();
		}
	}
	else if( loadingDt<1.0f )
	{
		// fade-in 보이기 처리
		setRGBA(0, 0, 0, 1.0f-(loadingDt-0.5f)/0.5f);
		fillRect(iRectMake(0, 0, devSize.width, devSize.height));
		setRGBA(1, 1, 1, 1);

		loadingDt += dt;
		if( loadingDt>=1.0f )
		{
			loadingDt = 0.0f;// end
			freeLoading();
			return;
		}
	}

	drawImage(texLoading, devSize.width-10, devSize.height-10, BOTTOM|RIGHT);

}
