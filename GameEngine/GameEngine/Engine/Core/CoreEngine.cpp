#include "CoreEngine.h"


std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine()
{
	// default values
	window = nullptr;
	isRunning = false;
	// set default max fps
	fps = 60;

	gameInterface = nullptr;
	currentScene = 0;
	camera = nullptr;
}


CoreEngine::~CoreEngine()
{
	OnDestroy();
}

// create the window
bool CoreEngine::onCreate(std::string name_, int widhth_, int height_)
{

	// create the debug
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	// initialize the window
	window = new Window();

	// checking if window is created
	if (!window->OnCreate(name_, widhth_, height_))
	{
		Debug::FatalError("Window Failed to create", __FILE__, __LINE__);

		// checking if window exists. If it does delete it
		if(window)
		{
			delete window;
			window = nullptr;
		}
		
		return isRunning = false;
	}
	SDL_WarpMouseInWindow(window->GetWindow(), window->getWidth() / 2, window->getHeight() / 2);

	ShaderHandler::GetInstance()->CreateProgram("ColourShader","Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("BasicShader","Engine/Shaders/VeretxShader.glsl", "Engine/Shaders/FragmentShader.glsl");
	MouseEventListener::RegisterEngineObject(getInstance());

	// create game interface
	if(gameInterface)
	{
		if(!gameInterface->OnCreate())
		{
			Debug::FatalError("Failed to create Game Interface", __FILE__, __LINE__);
			return isRunning = false;
		}
	}


	Debug::Info("Everything worked", __FILE__, __LINE__);
	// start the timer
	timer.Start();
	return isRunning = true;
}

// delete everything
void CoreEngine::OnDestroy()
{
	if(gameInterface)
	{
		delete gameInterface;
		gameInterface = nullptr;
	}
	if (camera)
	{
		delete camera;
		camera = nullptr;
	}
	if(window)
	{
		delete window;
		window = nullptr;
	}
	
	SDL_Quit();
	exit(0);
}

CoreEngine* CoreEngine::getInstance()
{
	if(engineInstance.get() == nullptr)
	{
		engineInstance.reset(new CoreEngine);
	}

	return engineInstance.get();
}

// run the engine method
void CoreEngine::Run()
{
	// call update and render
	while(isRunning)
	{
		EventListener::Update();
		timer.UpdateFramTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}

	// if it is not running call on destroy
	if(!isRunning)
	{
		OnDestroy();
	}

}

// return isRunning
bool CoreEngine::GetIsRunning()
{
	return isRunning;
}

// update the engine
void CoreEngine::Update(const float deltaTime_)
{
	if(gameInterface)
	{
		gameInterface->Update(deltaTime_);
	}
}


void CoreEngine::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(gameInterface)
	{
		gameInterface->Render();
	}

	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_)
{
	gameInterface = gameInterface_;
}

void CoreEngine::SetCurrentScene(int currentScene_)
{
	currentScene = currentScene_;
}

int CoreEngine::GetCurrentScene() const
{
	return currentScene;
}

glm::vec2 CoreEngine::GetScreenSize() const
{
	return glm::vec2(window->getWidth(), window->getHeight());
}

void CoreEngine::NotifyMousePressed(int x, int y)
{

}

void CoreEngine::NotifyMouseReleased(int x, int y, int buttonType_)
{

}

void CoreEngine::NotifyOfMouseMove(int x, int y)
{
	if(camera)
	{
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset().x, MouseEventListener::GetMouseOffset().y);

	}
}

void CoreEngine::NotifyOfMouseScroll(int y_)
{
	if (camera)
	{
		camera->ProcessMouseZoom(y_);

	}
}

void CoreEngine::ExitGame()
{
	isRunning = false;
}

void CoreEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

Camera* CoreEngine::GetCamera()
{
	return camera;
}


void CoreEngine::SetIsRunning(bool isRunning_)
{
	isRunning = isRunning_;
}


