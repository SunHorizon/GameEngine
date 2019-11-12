#include "Game0.h"



Game0::Game0() : GameInterface()
{
	CurrentScene = nullptr;
	sceneNum = 0;
}

Game0::~Game0()
{
	OnDestroy();
}

bool Game0::OnCreate()
{
	delete CurrentScene;
	if(CoreEngine::getInstance()->GetCurrentScene() == 0)
	{
		CurrentScene = new StartScene();
		if(!CurrentScene->OnCreate())
		{
			Debug::FatalError("Failed to create Scene ", __FILE__, __LINE__);
			return  false;
		}
	}
	sceneNum = 0;
	return true;
}

void Game0::Update(const float deltaTime_)
{
	if(sceneNum != CoreEngine::getInstance()->GetCurrentScene())
	{
		BuildScene();
	}
	CurrentScene->Update(deltaTime_);
	
}

void Game0::Render()
{
	CurrentScene->Render();
}

void Game0::OnDestroy()
{
	if(CurrentScene)
	{
		delete CurrentScene;
		CurrentScene = nullptr;
	}
}

void Game0::BuildScene()
{
	if (CurrentScene)
	{
		delete CurrentScene;
		CurrentScene = nullptr;
	}

	switch (CoreEngine::getInstance()->GetCurrentScene())
	{
		case 1:
			CurrentScene = new GameScene();
			break;
		default:
			CurrentScene = new StartScene();
			break;
	}
	if(!CurrentScene->OnCreate())
	{
		Debug::FatalError("Failed to create Scene ", __FILE__, __LINE__);
		CoreEngine::getInstance()->SetIsRunning(false);
	}
	sceneNum = CoreEngine::getInstance()->GetCurrentScene();
}

