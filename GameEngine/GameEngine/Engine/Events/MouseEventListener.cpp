#include "MouseEventListener.h"
#include "../Core/CoreEngine.h"


CoreEngine* MouseEventListener::engineInstance = nullptr;

int MouseEventListener::mouseX = 0;
int MouseEventListener::mouseY = 0;
int MouseEventListener::prevMouseX = 0;
int MouseEventListener::PrevMouseY = 0;

bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener()
{
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(CoreEngine* engine_)
{
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e_)
{
	switch (e_.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			UpdateMousePosition();
			NotifyMousePressed(e_.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			UpdateMousePosition();
			NotifyMouseReleased(e_.button.button);
			break;
		case SDL_MOUSEMOTION:
			UpdateMousePosition();
			NotifyOfMouseMove();
			break;
		case SDL_MOUSEWHEEL:
			UpdateMousePosition();
			NotifyOfMouseScroll(e_.wheel.y);
			break;
		default:
			break;
	}
}

void MouseEventListener::NotifyMousePressed(int buttonType_)
{
	if (engineInstance)
	{
		engineInstance->NotifyMousePressed(mouseX, mouseY);
	}
}

void MouseEventListener::NotifyMouseReleased(int buttonType_)
{
	if (engineInstance)
	{
		engineInstance->NotifyMouseReleased(mouseX, mouseY, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseMove()
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseMove(mouseX, mouseY);
	}
}

void MouseEventListener::NotifyOfMouseScroll(int y_)
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseScroll(y_);
	}
}

glm::vec2 MouseEventListener::GetPreviousMousePosition()
{
	return glm::vec2(prevMouseX, PrevMouseY);
}

glm::vec2 MouseEventListener::GetMousePosition()
{
	return glm::vec2(mouseX, mouseY);
}

glm::vec2 MouseEventListener::GetMouseOffset()
{
	return glm::vec2(mouseX - prevMouseX, PrevMouseY - mouseY);
}

void MouseEventListener::UpdateMousePosition()
{
	int tempX, tempY;
	SDL_GetMouseState(&tempX, &tempY);

	tempY = engineInstance->GetScreenSize().y - tempY;

	if(firstUpdate)
	{
		prevMouseX = mouseX;
		PrevMouseY = mouseY;
		firstUpdate = false;
	}
	else if(tempX != mouseX || tempY != mouseY)
	{
			prevMouseX = mouseX;
			PrevMouseY = mouseY;

			mouseX = tempX;
			mouseY = tempY;
	}
}
