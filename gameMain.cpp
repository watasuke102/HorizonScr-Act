#include "main.h"

void _gameMain::Init()
{
	const CSVData csv(U"Data/map.csv");
	double height = csv.columns(0);
	double wight  = csv.rows();
	mapData.Init(height, wight);
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
	static bool stp = false;
	if (KeyF5.down()) Init();
	if(!stp)
		player.Update(&mapData);
	if(KeyM.down())
		stp = !stp;
}

void _gameMain::Draw()
{
	Print << U"scr({})"_fmt(player.GetScr());
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
			HSV col(map * (360/9), 0.5);
			Rect((x*MAP_CHIPSIZE), y * MAP_CHIPSIZE, MAP_CHIPSIZE, MAP_CHIPSIZE)
				.draw(col);//(ColorF(0.6, 0.2, 0.2));
		}
	}
}