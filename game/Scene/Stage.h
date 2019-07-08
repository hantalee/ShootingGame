#pragma once

#include "iStd.h"


void loadStage();
void freeStage();
void drawStage(float dt);
void keyStage(iKeyState stat, iPoint point);
void stageCheckKey(float dt);


void loadObject();
void freeObject();
void drawObject(float dt);
void playerCheckKey();
