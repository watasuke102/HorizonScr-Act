#pragma once

class _mapData
{
private:
	Grid<int> map;
public:
	_mapData() { Init(0, 0); }
	void Init(int i,int j){ map = Grid<int>(i, j, 0); }
	int Width() { return map.width(); }
	int Height() { return map.height(); }
	void Set(int y, int x, int n)
	{
		if ( (y<0||y>map.width()) || (x<0 || x>map.height()) )
			return;
		map[y][x] = n;
		Print<<map[y][x]<<U"|"<<n;
	}
	int Get(int y, int x)
	{
		if ( (y<0||y>map.width()) || (x<0 || x>map.height()) )
			return 0;
		return map[y][x];
	}
};
class _player
{
private:
	Vec2 pos;
	Size size;
	bool didSpaceDown;
	int speed_x, speed_y, jumpCnt, jumpSp;
	int scr;
	bool debug;
public:
	void Init();
	void Update(_mapData*);
	void Draw();
	void CheckMapHit(_mapData*);
	int GetScr() { return scr; }
};