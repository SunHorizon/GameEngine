#include "StartScene.h"



StartScene::StartScene() : Scene()
{

}


StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	CoreEngine::getInstance()->SetCurrentScene(1);
	return true;
}

void StartScene::Update(const float deltaTime_)
{

}

void StartScene::Render()
{

}

void StartScene::OnDestroy()
{

}
