#include "main.h"

void GameInit()
{
	double resize = 0.8;
	Scene::SetBackground(ColorF(0.1));
	Graphics::SetTargetFrameRateHz(60);
	Window::SetStyle(WindowStyle::Sizable);
	//Window::Resize(WINDOW_X * resize, WINDOW_Y * resize);
	Window::Maximize();
	Scene::Resize(WINDOW_SIZE);

	FontAsset::Register(U"title", 255);
	FontAsset::Register(U"FPS", 20);
	FontAsset::Register(U"score", 25);
}

void Main()
{
	GameInit();
	_sceneManager scene;
	while (System::Update())
	{
		if (KeyLControl.pressed())
		{
			Stopwatch t;
			t.restart();
			while(t < 1s);
		}
		ClearPrint();
		Print <<U"\n\n\n\n";
		scene.Update();
	}
}


//3桁ごとにカンマで区切る
String SeparateString(String num)
{
	int length = num.length();
	String result;
	for (auto i:step(length))
	{
		result += num[(length-1)-i];
		if ((i+1)%3 == 0 && (i+1) != length && (i+1) != 0)
			result += U',';
	}
	return result.reverse();
}