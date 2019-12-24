#pragma once
//シーン管理
class _sceneManager
{
private:
	int now = sceneName::main;
	DynamicTexture fadePic;
	double col = 0;
	bool isFadeActive = false;
	bool makePic = false;
	//シーン
	_gameMain gameMain;
public:
	int Now() { return now; }
	void Change(int n)
	{
		ScreenCapture::RequestCurrentFrame();
		if (n != -1) now = n;
		isFadeActive = true;
		col = 0;
	}
	void Update()
	{
		//シーンの更新
		switch (now)
		{
		case sceneName::main: gameMain.Update(); break;
		}
		//フェードアウト処理
		if (isFadeActive)
		{
			if (col == 0)
				ScreenCapture::GetFrame(fadePic);
			fadePic.draw(0, 0, AlphaF(col));
			col += 0.05;
			if (col >= 1)
			{
				col = 0;
				isFadeActive = false;
			}
		}
	}
};