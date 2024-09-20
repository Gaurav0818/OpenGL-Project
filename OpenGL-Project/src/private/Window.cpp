#include "Window.h"

Window::Window()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
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
        std::cerr << "GLFW window Creation Failed";
        glfwTerminate();
        return;
    }

    // Get Buffer size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(m_window, &bufferWidth, &bufferHeight);

    // Set Conetext for GLFW to use 
    glfwMakeContextCurrent(m_window);

    // Allow modern extersion features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW initialization failed!";
        glfwDestroyWindow(m_window);
        glfwTerminate();
        return;
    }

    // Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
