#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>

#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"
#include "../Rendering/3D/GameObject.h"
#include "../Graphics/ShaderHandler.h"
#include "../../Engine/Camera/Camera.h"
#include "../Graphics/TextureHandler.h"
#include "../Events/EventListener.h"
#include "../Rendering/SceneGraph.h"

class CoreEngine
{
public:

	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	// get engine instance
	static CoreEngine* getInstance();

	
	bool onCreate(std::string name_, int widhth_, int height_);
	void Run();
	bool GetIsRunning();
	void SetIsRunning(bool isRunning_);
	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int currentScene_);
	int  GetCurrentScene() const;

	glm::vec2 GetScreenSize() const;

	void NotifyMousePressed(int x, int y);
	void NotifyMouseReleased(int x, int y, int buttonType_);
	void NotifyOfMouseMove(int x, int y);
	void NotifyOfMouseScroll(int y_);

	void ExitGame();

	void SetCamera(Camera* camera_);
	Camera* GetCamera();
private:
	CoreEngine();
	~CoreEngine();

	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	static  std::unique_ptr<CoreEngine> engineInstance;
	friend  std::default_delete<CoreEngine>;

	Window* window;
	Timer timer;
	GameInterface* gameInterface;
	bool isRunning;
	unsigned int fps;
	int currentScene;

	Camera* camera;
};
#endif


