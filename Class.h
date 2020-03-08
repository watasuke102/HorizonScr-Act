#pragma once

//マップのデータ管理
class _mapData
{
private:
	Grid<int> map;
	Vec2 playersp;
	int scr;

public:
	_mapData() { Init(0, 0); }
	void Init(int i,int j){ map = Grid<int>(i, j, 0); }
	int Width() { return map.width(); }
	int Height() { return map.height(); }
	int SizeGet() { return map.size_bytes(); }
	int GetScr() { return scr; }
	Vec2 GetPlayerSpeed() { return playersp; }

	void SetScr(int a){ scr=a; }
	void SetPlayerSpeed(Vec2 a) { playersp = a; }
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
	//描画用ステータス
	Texture pic;
	Vec2 pos, drawPos, speed;
	RectF hitBox;
	int scr;
	//ジャンプ
	bool didSpaceDown;
	int jumpCnt, spacePressedFrame;
	//ダッシュ
	Effect afterImage;
	int dashingTime;
	int dashSp; //1→右、-1→左
	bool dashing;

	bool debug;
public:
	void Init();
	void Update(_mapData*);
	void Draw();
	void DebugDraw();

	void Dash();
	void Jump();
	void Move(_mapData*);
	int GetScr() { return scr; }
};

class _enemy
{
private:
	Vec2 pos;
	Vec2 speed;
	RectF hitBox;
public:
	void Init();
	void Update(_mapData*);
	void Draw();
};

