#include "main.h"

void Main()
{
	Graphics::SetTargetFrameRateHz(56);
	double resize = 0.8;
	Window::SetStyle(WindowStyle::Sizable);
	Window::Resize(WINDOW_X * resize, WINDOW_Y * resize);
	Scene::Resize(WINDOW_SIZE);
	Window::Maximize();

	_sceneManager scene;
	_fpsManager fpsManager;
	while (System::Update())
	{
		ClearPrint();
		scene.Update();
		fpsManager.Update();
	}
}
