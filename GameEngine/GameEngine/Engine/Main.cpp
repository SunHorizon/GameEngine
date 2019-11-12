#include <iostream>
#include "Core/CoreEngine.h"
#include "../Game/Game0.h"

int main(int argc, char* argv[])
{
	CoreEngine::getInstance()->SetGameInterface(new Game0());

	// check if engine is created
	if (!CoreEngine::getInstance()->onCreate("Game Engine", 800, 600))
	{
		Debug::FatalError("Failed to create engine", __FILE__, __LINE__);
		return 0;
	}

	// run the engine
	CoreEngine::getInstance()->Run();


	std::getchar();
	return 0;
}