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
	void Set(int i, int j, int n)
	{
		//if ( (i<0||i>map.width()) || (j<0 || j>map.height()) )
		//	return;
		map[i][j] = n;
		Print<<map[i][j]<<U"|"<<n;
	}
	 int Get(int i, int j) { return map[i][j]; }
	 int* operator[](int i) { return map[i]; }
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