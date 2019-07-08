#pragma once

#include "iStd.h"

extern iPopup* popOption;

void createOptionPop();
void freeOptionPop();
void drawOptionPop(float dt);
void drawPopOptionBtnBefore(void* parm, iPoint point, float scale, float alpha, float dt);
bool keyOptionPop(iKeyState stat, iPoint point);
