﻿#pragma once

#include <Siv3D.hpp>
#include <time.h>
#define GL __declspec(selectany)


constexpr int WINDOW_X = 1920;
constexpr int WINDOW_Y = 1080;
constexpr Size WINDOW_SIZE(WINDOW_X,WINDOW_Y);

constexpr int PLAYER_SPEED     =  8;
constexpr int PLAYER_HIGHSPEED = 12;
constexpr int JUMP_POWER       =  15;

constexpr int MAP_CHIPSIZE   = 60;

namespace sceneName
{
	const int title = 0;
	const int main  = 1;
};
typedef struct
{
	bool top, bottom, left, right;
	Vec2 pos;
}_mapHitState;

#include"Class.h"
#include"Scene.h"
#include"SceneManager.h"
//#include"CheckMapHit.h"


extern String SeparateString(String);
extern _mapHitState CheckMapHit(_mapData*, Vec2, Rect, Vec2);