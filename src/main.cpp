// main.cpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "utilities/Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int currentDrawMode = 0;
void switchDrawMode()
{
    if (currentDrawMode == 0)
    {
        currentDrawMode = 1;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        currentDrawMode = 0;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        switchDrawMode();
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set window flags
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window with OpenGL context
    const int WIN_WIDTH = 1280;
    const int WIN_HEIGHT = 720;
    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "GLFW Test Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Triangle data
    float triangleOne[] = {
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, 0.5f, 0.0f, // top left
    };

    float triangleTwo[] = {
        -0.5f, 0.5f, 0.0f, // top left
        0.5f, -0.5f, 0.0f, // bottom right
        0.5f, 0.5f, 0.0f, // top right
    };

    // Color data
    float colorData[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
    };

    // ==================================
    // Triangle ONE
    // ==================================
    // Generate VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate VBO to go into VAO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleOne), triangleOne, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    // Generate VBO for color
    unsigned int ColorVBO;
    glGenBuffers(1, &ColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, ColorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(1);
    
    // ==================================
    // Triangle TWO
    // ==================================
    // Generate VAO2
    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    // Generate VBO to go into VAO2
    unsigned int VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleTwo), triangleTwo, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    // Bind the same ColorVBO to VAO2
    glBindBuffer(GL_ARRAY_BUFFER, ColorVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(1);

    Shader normalShader("default_vertex.glsl", "default_fragment.glsl");
    Shader yellowShader("default_vertex.glsl", "yellow_fragment.glsl");

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the back buffer with the color bit set earlier
        glClear(GL_COLOR_BUFFER_BIT);
            
        // Process input
        processInput(window);

        // Calculating time value and sine value
        float timeValue = glfwGetTime();
        float sineValue = sin(timeValue) * 0.8f;

        // Use default shader and set top offset uniform
        normalShader.use();
        normalShader.setVec3f("topOffset", sineValue, 0.0f, 0.0f);

        // Bind the first bottom left triangle and draw it
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Use the yellow shader and set the app colors uniform
        yellowShader.use();
        yellowShader.setVec4f("appColors", sineValue, sineValue, 0, 0);

        // Bind the second top right triangle and draw it
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap the front buffer and back buffer
        glfwSwapBuffers(window);

        // Check for any events
        glfwPollEvents();
    }

    // Cleanup and exit
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}