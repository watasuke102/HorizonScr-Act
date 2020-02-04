#include "main.h"

void _title::Init(){}
void _title::Update()
{
	if (KeySpace.down())
		sceneChange.Start(sceneName::main);
}
void _title::Draw()
{
	FontAsset(U"title")(U"T I T L E").drawAt(Scene::Center());
}