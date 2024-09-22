#pragma once

#include "Config.h"

class Window
{
public:
	Window();
	~Window();

	GLFWwindow* getWindow() const { return m_window; }
	int getBufferWidth() const { return m_bufferWidth; }
	int getBufferHeight() const { return m_bufferHeight; }

private:
	GLFWwindow* m_window;
	int m_bufferWidth, m_bufferHeight;
};

extern std::unique_ptr<Window> g_activeWindow;
