#pragma once

#include "Config.h"

class Window
{
public:
	Window();
	~Window();

	GLFWwindow* getWindow() const { return m_window; }

private:
	GLFWwindow* m_window;
};
