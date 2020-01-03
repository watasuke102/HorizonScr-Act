#pragma once

//FPSの計算・固定
class _fpsManager
{
private:
	const int limitFPS = 60;
	int cnt;
	int startTime;
	int progressTime;
	double fps;
	Font font;

public:
	_fpsManager()
	{
		font = Font(20);
		cnt = 0;
		startTime = Time::GetMicrosec();
		progressTime = 0;
		fps = 0;
	}
	void Update()
	{
		//指定FPSになるように待機
		progressTime = Time::GetMicrosec() - startTime;
		int wait = cnt * 1000 / limitFPS - progressTime;
		if (wait > 0) System::Sleep(wait);

		//FPSの計算
		if (cnt == 0) startTime = Time::GetMicrosec();
		if (cnt == limitFPS)
		{
			int time = Time::GetMicrosec();
			fps = 1000.0 / ((time - startTime) / (double)limitFPS);
			cnt = 0;
			startTime = time;
		}
		cnt++;
		//FPSの表示
		Print << fps;
		font(U"FPS[{:0>4.2f}]"_fmt(fps)).draw(Arg::bottomRight(WINDOW_X,WINDOW_Y));
	}
};

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

//プレイヤー
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