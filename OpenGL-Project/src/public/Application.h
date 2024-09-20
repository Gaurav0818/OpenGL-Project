#pragma once

#include "Config.h"

#include "Shader.h"
#include "Window.h"
#include "Mesh.h"

class Application
{
public:
	Application();
	~Application() = default;

	void run();

private:
	std::unique_ptr<Window> m_window;
};
