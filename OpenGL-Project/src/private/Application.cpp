#include "Application.h"

Application::Application()
{
    g_activeWindow = std::make_unique<Window>();
}

void Application::run()
{
    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();

    // Define a View matrix (our camera)
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 10.0f), // Moved camera back a bit
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    // --- State & Animation Variables ---
    float rotationAngle = 0.0f;
    float rotationSpeed = 20.0f;
    float travelDistance = 6.0f;
    float travelSpeed = 1.5f;

    // State variables for toggles
    bool shouldRotate = true;
    bool shouldMove = true;

    // State variables for tessellation levels
    float tessLevelInner = 4.0f;
    float tessLevelOuter = 4.0f;

    // --- Camera Distance (Zoom) Variables
    float cameraDistance = 10.0f;
    float zoomSpeed = 5.0f;
    const float minDistance = 2.0f;
    const float maxDistance = 25.0f;

    // --- Color State Variables
    std::vector<glm::vec3> colors = {
        {0.0f, 0.75f, 0.75f},   // Cyan
        {1.0f, 0.5f, 0.0f},    // Orange
        {0.8f, 0.1f, 0.8f},    // Purple
        {0.2f, 0.9f, 0.3f}     // Green
    };
    int colorIndex = 0;

    // Variables for key press debounce (to register a press only once)
    int rKeyState = GLFW_RELEASE;
    int mKeyState = GLFW_RELEASE;
    int cKeyState = GLFW_RELEASE;

    double lastTime = glfwGetTime();

    // Loop until window closed
    while (!glfwWindowShouldClose(g_activeWindow->getWindow()))
    {
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        // --- Handle Keyboard Input ---
        glfwPollEvents();

        // Toggle Rotation with 'R' key
        if (glfwGetKey(g_activeWindow->getWindow(), GLFW_KEY_R) == GLFW_PRESS && rKeyState == GLFW_RELEASE) {
            shouldRotate = !shouldRotate;
        }
        rKeyState = glfwGetKey(g_activeWindow->getWindow(), GLFW_KEY_R);

        // Toggle Movement with 'M' key
        if (glfwGetKey(g_activeWindow->getWindow(), GLFW_KEY_M) == GLFW_PRESS && mKeyState == GLFW_RELEASE) {
            shouldMove = !shouldMove;
        }
        mKeyState = glfwGetKey(g_activeWindow->getWindow(), GLFW_KEY_M);

        // Cycle Color with 'C' key
        if (glfwGetKey(g_activeWindow->getWindow(), GLFW_KEY_C) == GLFW_PRESS && cKeyState == GLFW_RELEASE) {
            colorIndex = (colorIndex + 1) % colors.size();
        }
        cKeyState = glfwGetKey(g_activeWindow->getWindow(), GLFW_KEY_C);

        // Adjust Tessellation with Arrow Keys
        if (glfwGetKey(g_activeWindow->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) tessLevelOuter += 2.0f * deltaTime;
        if (glfwGetKey(g_activeWindow->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) tessLevelOuter -= 2.0f * deltaTime;
        if (glfwGetKey(g_activeWindow->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) tessLevelInner += 2.0f * deltaTime;
        if (glfwGetKey(g_activeWindow->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) tessLevelInner -= 2.0f * deltaTime;

        // Clamp tessellation levels to a minimum of 1.0
        if (tessLevelOuter < 1.0f) tessLevelOuter = 1.0f;
        if (tessLevelInner < 1.0f) tessLevelInner = 1.0f;

        // --- Adjust Camera Distance with W/S Keys --- 🔭
        if (glfwGetKey(g_activeWindow->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
            cameraDistance -= zoomSpeed * deltaTime;
        }
        if (glfwGetKey(g_activeWindow->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
            cameraDistance += zoomSpeed * deltaTime;
        }

        // Clamp the camera distance to the defined min/max range
        cameraDistance = glm::clamp(cameraDistance, minDistance, maxDistance);


        // --- Update Animation Based on State ---
        if (shouldMove) {
            float xPos = sin((float)currentTime * travelSpeed) * (travelDistance / 2.0f);
            mesh->pos = glm::vec3(xPos, 0.0f, 0.0f);
        }

        if (shouldRotate) {
            rotationAngle += rotationSpeed * deltaTime;
        }
        mesh->angle = rotationAngle;
        mesh->rotationAxis = glm::vec3(0.0f, 1.0f, 0.5f);

        // --- Update View Matrix (Camera) ---
        // This is now inside the loop to use the dynamic cameraDistance
        glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 0.0f, cameraDistance),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        // --- Draw Frame ---
        glClearColor(1.0f, 0.6f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Pass the tessellation levels to the draw call
        mesh->draw(view, tessLevelInner, tessLevelOuter, colors[colorIndex]);

        glfwSwapBuffers(g_activeWindow->getWindow());
    }
}
