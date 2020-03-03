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
	enemy.Init();
	MapDraw();
	stageElapsedTime.restart();
}
void _gameMain::Update()
{
	static bool stp = false;
	if (KeyF5.down()) Init();
	if(!stp) player.Update(&mapData);
	enemy.Update(&mapData);
	if(KeyM.down())
		stp = !stp;
}
void _gameMain::Draw()
{
	Print << U"scr({})"_fmt(player.GetScr());
	map.draw(player.GetScr(), 0);
	player.Draw();
	enemy.Draw();
	//UI
	Rect(50, 50, 400  , 50).shearedX(10).draw(Palette::Gray);
	Rect(50, 50, 400/4, 50).shearedX(10).draw(ColorF(0.9,0.15,0.1));
	String score = U"{:0>12}"_fmt(U"123456789");
	FontAsset(U"score")(U"TIME:{}   SCORE:{}"_fmt(stageElapsedTime, SeparateString(score))).draw(0, 0);
	FontAsset(U"FPS")( U"FPS[{:0>2}]"_fmt(Profiler::FPS()) ).draw(Arg::bottomRight(WINDOW_X, WINDOW_Y));
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