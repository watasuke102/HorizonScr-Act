#pragma once
//シーン管理
struct _sceneChange
{
	bool willChangeStart;
	int nextScene;
	void start(bool f,int next)
	{
		willChangeStart=f;
		nextScene = next;
	}
} GL sceneChange;
class _sceneManager
{
private:
	int now = sceneName::main;
	DynamicTexture fadePic;
	double col = 0;
	Stopwatch fadeDuration;
	bool isFadeActive = false;
	bool makePic = false;
	//シーン
	_gameMain gameMain;
public:
	void Change(int n)
	{
		ScreenCapture::RequestCurrentFrame();
		if (n != -1) now = n;
		isFadeActive = true;
		fadeDuration.reset();
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
			if (!fadeDuration.isRunning())
			{
				ScreenCapture::GetFrame(fadePic);
				fadeDuration.restart();
			}
			fadePic.draw(0, 0, AlphaF(1.0-fadeDuration.sF()/0.5));
			if (fadeDuration > 0.5s)
			{
				fadeDuration.reset();
				isFadeActive = false;
			}
		}
		//シーンチェンジ開始
		if(sceneChange.willChangeStart)
		{
			ScreenCapture::RequestCurrentFrame();
			if (sceneChange.nextScene != -1)
				now = sceneChange.nextScene;
			isFadeActive = true;
			fadeDuration.reset();
		}
	}
};