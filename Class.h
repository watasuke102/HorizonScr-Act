#pragma once

//マップのデータ管理
class _mapData
{
private:
	Grid<int> map;
public:
	_mapData() { Init(0, 0); }
	void Init(int i,int j){ map = Grid<int>(i, j, 0); }
	int Width() { return map.width(); }
	int Height() { return map.height(); }
	int Sizeget() { return map.size_bytes(); }
	void Set(int y, int x, int n)
	{
		if (y<0 || y>map.height() || x<0 || x>map.width())
			return;
		map[y][x] = n;
	}
	int Get(int y, int x)
	{
		if ( (y<0||y>map.height()) || (x<0 || x>map.width()) )
			return 0;
		return map[y][x];
	}
};

//プレイヤー
class _player
{
private:
	Vec2 pos, speed;
	Size size;
	RenderTexture debugtxr;
	bool didSpaceDown;
	int jumpCnt, spacePressedFrame;
	int scr;
	//ダッシュ
	Effect afterImage;
	Stopwatch dashingTime;
	int dashSp; //1→右、-1→左
	bool dashing;

	bool debug;
public:
	void Init();
	void Update(_mapData*);
	void Draw();

	void Dash();
	void Jump();
	void Move(_mapData*);
	void CheckMapHit(_mapData*);
	int GetScr() { return scr; }
};