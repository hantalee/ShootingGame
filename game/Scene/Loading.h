#pragma once

#include "iStd.h"

typedef enum _GameState {
	g_intro = 0,
	g_menu,
	g_stage,
	g_end
} GameState;

extern GameState gameState;

typedef void (*LOADING_METHOD)();

void setLoading(GameState gs, LOADING_METHOD methodFree, LOADING_METHOD methodLoad);
void drawLoading(float dt);
