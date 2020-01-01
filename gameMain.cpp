#include "main.h"

void _gameMain::Init()
{
	const CSVData csv(U"Data/map.csv");
	mapData.Init(csv.columns(0), csv.rows());
	//mapData.Init(50,50);
	for (auto y : step(mapData.Height()))
	for (auto x : step(mapData.Width()))
	{
		int n = Parse<int>(csv[y][x]);
		mapData.Set(y, x, n);
	}

	player.Init();
	String dev,out;
	//Height18:Width50
	for (auto y : step(mapData.Height()))
	{
		dev.clear();
		for (auto x : step(mapData.Width()))
			dev += U"{},"_fmt(mapData.Get(y, x));
		out +=(U"{"+dev+U"} ,\n");
	}
	TextWriter t(U"CSV.txt");
	t.writeln(out);
	t.close();
}
void _gameMain::Update()
{
	Print << U"W{}, H{}"_fmt(mapData.Width(), mapData.Height());
	player.Update(&mapData);
	Draw();
}
/**/
void _gameMain::Draw()
{
	for (auto y : step(mapData.Height()))
	for (auto x : step(mapData.Width()))
		if (mapData[y][x] != 0)
		{
			//if (mapData[y][x] == 2)
			//{
			//	Vec2 leftTop(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE);
			//	Triangle(leftTop.x, leftTop.y, MAP_CHIPSIZE).draw(ColorF(0.2, 0.6, 0.2));
			//	continue;
			//}
			Rect((x*MAP_CHIPSIZE)+scr, y * MAP_CHIPSIZE, MAP_CHIPSIZE, MAP_CHIPSIZE)
				.draw(ColorF(0.6, 0.2, 0.2));
		}

	player.Draw();
}
/*/
void _gameMain::Draw()
{
	for (auto j : step(mapData.Height()))
	for (auto i : step(mapData.Width()))
		if (mapData.Get(j,i) != 0)
		{
			if (mapData.Get(j,i) == 2)
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
/**/