#include "Game.h"

#include "Intro.h"
#include "Menu.h"
#include "Loading.h"
#include "Stage.h"

#include "OptionBtn.h"


void loadGame()
{
	loadIntro();
	gameState = g_intro;

	createPopExit();
	createOptionPop();
}

void freeGame()
{
	switch( gameState ) {
	case g_intro: 	freeIntro(); break;
	case g_menu: 	freeMenu(); break;
	case g_stage:	freeStage(); break;
	case g_end: break;
	}

	freePopExit();
	freeOptionPop();
}

void drawGame(float dt)
{
	float _dt = dt;
	if( popExit->bShow )
		dt = 0.0f;

	switch( gameState ) {
	case g_intro: 	drawIntro(dt); break;
	case g_menu:	drawMenu(dt); break;
	case g_stage:	drawStage(dt); break;
	case g_end: break;
	}

	drawLoading(dt);

	drawPopExit(_dt);
	drawOptionPop(_dt);
}

void keyGame(iKeyState stat, iPoint point)
{
	if( keyOptionPop(stat, point) ||
		keyPopExit(stat, point) )
		return;

	switch( gameState ) {
	case g_intro: 	keyIntro(stat, point); break;
	case g_menu:	 keyMenu(stat, point); break;
	case g_stage:	keyStage(stat, point); break;
	case g_end: break;
	}
}



