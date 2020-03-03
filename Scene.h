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
	_enemy enemy;

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