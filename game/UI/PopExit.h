#pragma once

#include "iStd.h"

extern iPopup* popExit;

void createPopExit();
void freePopExit();
void showPopExit(bool show);
void drawPopExit(float dt);
void drawPopExitBefore(void* parm, iPoint point, float scale, float alpha, float dt);
bool keyPopExit(iKeyState stat, iPoint point);
