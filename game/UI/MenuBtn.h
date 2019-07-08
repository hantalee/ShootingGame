#pragma once

#include "iStd.h"

#define MN_BTN_NUM 3

#define MN_START 	0
#define MN_OPTION 	1
#define MN_EXIT 	2

void createMenuBtn();
void freeMenuBtn();
void drawMenuBtn(float dt);
bool keyMenuBtn(iKeyState stat, iPoint point);


