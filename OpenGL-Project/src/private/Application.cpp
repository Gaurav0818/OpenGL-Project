#include "Application.h"

Application::Application()
{
    g_activeWindow = std::make_unique<Window>();
}

void Application::run()
{
    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
    mesh->pos = glm::vec3(0.0f, 0.5f, -3.0f);
    int dir = 1;
    float value = 10;
    float inc = 1;
    float min = 0.1;
    int max = 1;

    // Loop until window closed
    while (!glfwWindowShouldClose(g_activeWindow->getWindow()))
    {
        // Get + Handle user input Events 
        glfwPollEvents();

        // Clear Window
        glClearColor(1.0f, 0.6f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        value += inc;
       
        mesh->rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
        mesh->angle = value;

        mesh->draw();

        glfwSwapBuffers(g_activeWindow->getWindow());
    }
}
