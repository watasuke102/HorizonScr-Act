#pragma once

class _title
{
public:
	_title() { Init(); }
	void Init();
	void Update();
	void Draw();
};

class _gameMain
{
private:
	_player player;
	_mapData mapData;
	RenderTexture map;
	Stopwatch stageElapsedTime;
public:
	_gameMain() { Init(); }
	void Init();
	void Update();
	void Draw();

	void MapDraw();
};