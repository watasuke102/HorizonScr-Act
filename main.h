#pragma once

#include <Siv3D.hpp>
#define GL __declspec(selectany)

constexpr int WINDOW_X = 1920;
constexpr int WINDOW_Y = 1080;
constexpr Size WINDOW_SIZE(WINDOW_X,WINDOW_Y);

constexpr int PLAYER_SPEED     =  8;
constexpr int PLAYER_HIGHSPEED = 12;
constexpr int JUMP_POWER       =  5;

constexpr int MAP_CHIPSIZE   = 60;
constexpr int MAP_WIDTH      = 41;
constexpr int MAP_HEIGHT     = 18;

namespace sceneName
{
	const int main = 0;
};

#include"Class.h"
#include"Scene.h"
#include"SceneManager.h"