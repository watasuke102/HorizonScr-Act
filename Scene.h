#pragma once

class _gameMain
{
private:
	_player player;
	_mapData mapData;
	RenderTexture map;
public:
	_gameMain() { Init(); }
	void Init();
	void Update();
	void Draw();

	void MapDraw();
};