#ifndef MouseEventListener_H
#define MouseEventListener_H
#include <memory>

#include <SDL.h>
#include <glm/glm.hpp>


class CoreEngine;
class MouseEventListener
{
public:

	MouseEventListener() = delete;
	~MouseEventListener();

	MouseEventListener(const MouseEventListener&) = delete;
	MouseEventListener(MouseEventListener&&) = delete;
	MouseEventListener& operator=(const MouseEventListener&) = delete;
	MouseEventListener& operator=(MouseEventListener&&) = delete;

	
	static void RegisterEngineObject(CoreEngine* engine_);
	static void Update(SDL_Event e_);
	static void NotifyMousePressed(int buttonType_);
	static void NotifyMouseReleased(int buttonType_);
	static void NotifyOfMouseMove();
	static void NotifyOfMouseScroll(int y_);
	static glm::vec2 GetPreviousMousePosition();
	static glm::vec2 GetMousePosition();
	static glm::vec2 GetMouseOffset();

private:

	friend  std::default_delete<MouseEventListener>;

	static CoreEngine* engineInstance;
	static int mouseX, mouseY, prevMouseX, PrevMouseY;
	static bool firstUpdate;

	static void UpdateMousePosition();
};
#endif //!MouseEventListener_H
