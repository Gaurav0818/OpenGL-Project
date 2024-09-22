#include "Window.h"

std::unique_ptr<Window> g_activeWindow = nullptr;

Window::Window()
{
    if (!glfwInit()) {
        Logger::Error("Failed to initialize GLFW!");
        glfwTerminate();
        return;
    }

    //OpenGL Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // Core profile = no backword compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow Forword Compatibility 
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    m_window = glfwCreateWindow(WIDTH, HEIGHT, "Open GL Window", NULL, NULL);

    if (!m_window)
    {
        Logger::Error("GLFW window Creation Failed");
        glfwTerminate();
        return;
    }

    glfwGetFramebufferSize(m_window, &m_bufferWidth, &m_bufferHeight);

    // Set Conetext for GLFW to use 
    glfwMakeContextCurrent(m_window);

    // Allow modern extersion features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        Logger::Error("GLEW initialization failed!");
        glfwDestroyWindow(m_window);
        glfwTerminate();
        return;
    }

    glEnable(GL_DEPTH_TEST);

    // Setup viewport size
    glViewport(0, 0, m_bufferWidth, m_bufferHeight);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
