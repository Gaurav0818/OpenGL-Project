#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int WIDTH = 800, HEIGHT = 600;

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        glfwTerminate();
        return -1;
    }

    //OpenGL Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // Core profile = no backword compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow Forword Compatibility 
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Open GL Window", NULL, NULL);

    if (!mainWindow)
    {
        std::cerr << "GLFW window Creation Failed";
        glfwTerminate();
        return 1;
    }

    // Get Buffer size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set Conetext for GLFW to use 
    glfwMakeContextCurrent(mainWindow);

    // Allow modern extersion features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW initialization failed!";
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    // Loop until window closed
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Get + Handle user input Events 
        glfwPollEvents();

        // Clear Window
        glClearColor(1.0f, 0.6f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mainWindow);
    }

    return 0;
}
