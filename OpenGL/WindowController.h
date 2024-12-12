#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_H

#include "StandardIncludes.h"

class WindowController : public Singleton<WindowController>
{
public:
	// Constructors / Destructors
	WindowController();
	virtual ~WindowController();

	void Create(int _width = -1, int _height = -1);

	// Accessors
	GLFWwindow* GetWindow() { if (window == nullptr){ NewWindow(); } return window;
}

	// Methods
	void NewWindow();
	const Resolution& GetResolution() { return resolution; }

private:
	// Members
	GLFWwindow* window;
	Resolution resolution = { 1280, 768 };
};

#endif // WINDOW_CONTROLLER_H