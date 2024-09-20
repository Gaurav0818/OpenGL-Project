#include "Application.h"

Application::Application()
{
    m_window = std::make_unique<Window>();
}

void Application::run()
{
    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();

    int dir = 1;
    float value = 0.5;
    float inc = 0.01;
    float min = 0.1;
    int max = 1;

    // Loop until window closed
    while (!glfwWindowShouldClose(m_window->getWindow()))
    {
        // Get + Handle user input Events 
        glfwPollEvents();

        // Clear Window
        glClearColor(1.0f, 0.6f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        value += inc * dir;

        if (value > max || value < min)
            dir = dir * -1;

        mesh->scale = glm::vec3(value);

        mesh->draw();

        glfwSwapBuffers(m_window->getWindow());
    }
}
