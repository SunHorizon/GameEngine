#include "Window.h"



Window::Window()
{
	// default value
	window = nullptr;
	width = 0;
	height = 0;
}

// create the window 
bool Window::OnCreate(std::string name_, int width_, int height_)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Debug::FatalError("Failed to initialize SDL", __FILE__, __LINE__);
		return false;
	}

	// set width
	width = width_;
	height = height_;

	// create window
	window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	if(!window)
	{
		Debug::FatalError("Failed to create window", __FILE__, __LINE__);
		return false;
	}

	// set context
	context = SDL_GL_CreateContext(window);
	SetAttributes();

	// check error
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		Debug::FatalError("Failed to initialize", __FILE__, __LINE__);
		return false;;
	}

	glEnable(GL_DEPTH_TEST);
	return true;
}

// delete everything
void Window::onDestroy()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);

	window = nullptr;
	
}

// set window attributes
void Window::SetAttributes()
{

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;
}

// get width
int Window::getWidth()
{
	return width;
}
// get height
int Window::getHeight()
{
	return height;
}

// get window
SDL_Window* Window::GetWindow() const
{
	return window;
}

Window::~Window()
{
	onDestroy();
}
