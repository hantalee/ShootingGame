#pragma once

#include "iStd.h"


#define PS_BTN_NUM 4

#define PS_RESTART 	0
#define PS_MENU 	1
#define PS_OPTION 	2
#define PS_EXIT 	3

extern iPopup* popPause;

void createPause();
void freePause();
void drawPause(float dt);
bool keyPause(iKeyState stat, iPoint point);
void drawPauseBtnBefore(void* parm, iPoint point, float scale, float alpha, float dt);
