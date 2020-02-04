#pragma once
//シーン管理
struct _sceneChange
{
	bool willChangeStart;
	int nextScene;
	void Start(int next)
	{
		ScreenCapture::RequestCurrentFrame();
		willChangeStart=true;
		nextScene = next;
	}
} GL sceneChange;
class _sceneManager
{
private:
	int now = sceneName::title;
	DynamicTexture fadePic;
	Stopwatch fadeDuration;
	double col = 0;
	bool isFadeActive = false;
	bool makePic = false;
	//シーン
	_title title;
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
			case sceneName::title:   title.Update(); break;
			case sceneName::main: gameMain.Update(); break;
		}
		//シーンの描画
		switch (now)
		{
			case sceneName::title:   title.Draw(); break;
			case sceneName::main: gameMain.Draw(); break;
		}
		//フェードアウト処理
		if (isFadeActive)
		{
			if (!fadeDuration.isRunning())
			{
				ScreenCapture::GetFrame(fadePic);
				fadeDuration.restart();
			}
			fadePic.draw(0, 0, AlphaF(1.0 - fadeDuration.sF()/0.5));
			if (fadeDuration > 0.5s)
			{
				fadeDuration.reset();
				isFadeActive = false;
			}
		}
		//シーンチェンジ開始
		if(sceneChange.willChangeStart)
		{
			isFadeActive = true;
			sceneChange.willChangeStart=false;
			now = sceneChange.nextScene;
			ScreenCapture::RequestCurrentFrame();
			fadeDuration.reset();
		}
	}
};