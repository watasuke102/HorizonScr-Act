#include "main.h"

void _gameMain::Init()
{
	const CSVData csv(U"Data/map.csv");
	mapData.Init(csv.columns(0), csv.rows());
	for (auto y : step(mapData.Height()))
	for (auto x : step(mapData.Width()))
	{
		int n = Parse<int>(csv[y][x]);
		mapData.Set(y, x, n);
	}

	player.Init();

	String dev,out;
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

	MapDraw();
}
void _gameMain::Update()
{
	if (KeyF5.down()) Init();
	player.Update(&mapData);
	Draw();
}
/**/
void _gameMain::Draw()
{
	Print << player.GetScr();
	map.draw(player.GetScr(), 0);
	player.Draw();
}
void _gameMain::MapDraw()
{
	Size mapSize(mapData.Width() * MAP_CHIPSIZE, mapData.Height() * MAP_CHIPSIZE);
	//map.resized(mapSize);
	map = RenderTexture(mapSize,ColorF(0.1));
	ScopedRenderTarget2D target(map);
	for (auto y : step(mapData.Height()))
	for (auto x : step(mapData.Width()))
	{
		int map = mapData.Get(y, x);
		if (map != 0)
		{
			/*
			if (map == 2)
			{
				Vec2 leftTop(x * MAP_CHIPSIZE, y * MAP_CHIPSIZE);
				Triangle(leftTop.x, leftTop.y, MAP_CHIPSIZE).draw(ColorF(0.2, 0.6, 0.2));
				continue;
			}
			*/
			HSV col(map * (360/9), 0.5);
			Rect((x*MAP_CHIPSIZE), y * MAP_CHIPSIZE, MAP_CHIPSIZE, MAP_CHIPSIZE)
				.draw(col);//(ColorF(0.6, 0.2, 0.2));
		}
	}
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