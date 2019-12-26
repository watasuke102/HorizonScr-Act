#include "main.h"

void _gameMain::Init()
{
	player.Init(mapData);
}
void _gameMain::Update()
{
	player.Update();
	Draw();
}
void _gameMain::Draw()
{
	for (auto i : step(MAP_HEIGHT))
	for (auto j : step(MAP_WIDTH))
		if (mapData[i][j] != 0)
		{
			if (mapData[i][j] == 2)
			{
				Vec2 leftTop(j * MAP_CHIPSIZE, i * MAP_CHIPSIZE);
				Triangle(leftTop.x, leftTop.y, MAP_CHIPSIZE).draw(ColorF(0.2, 0.6, 0.2));
				continue;
			}
			Rect((j*MAP_CHIPSIZE)+player.GetScr(), i * MAP_CHIPSIZE, MAP_CHIPSIZE, MAP_CHIPSIZE)
				.draw(ColorF(0.6, 0.2, 0.2));
		}

	player.Draw();
}