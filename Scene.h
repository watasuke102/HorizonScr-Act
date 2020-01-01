#pragma once

class _gameMain
{
private:
	int scr;
	_player player;
	_mapData mapData;
public:
	_gameMain() { Init(); }
	void Init();
	void Update();
	void Draw();
};