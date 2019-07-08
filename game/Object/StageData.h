#pragma once

#include "iStd.h"

#define STAGE_NUM 3
#define ENEMY_NUM 10
#define ENEMY_TYPE_NUM 2

typedef enum _EnemyType
{
	EnemyType_none = -1,
	EnemyType_nomal = 0,
	EnemyType_Fast,
}EnemyType;

typedef struct _EnemyList
{
	EnemyType index;
	iPoint position;
}EnemyList;

typedef struct _StageInfo
{
	int length;
	int half;
	EnemyList enemyList[ENEMY_NUM];
}StageInfo;

extern StageInfo stageInfo[STAGE_NUM];
