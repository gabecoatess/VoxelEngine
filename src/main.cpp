// main.cpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "utilities/Shader.h"
#include "thirdparty/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int currentDrawMode = 0;
bool fKeyPressed = false;
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

    bool isFPressed = (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS);
    if (isFPressed && !fKeyPressed)
    {
        switchDrawMode();
    }

    fKeyPressed = isFPressed;
}

int currentColor = 0;
glm::vec3 switchScreenColor()
{
    glm::vec3 totalColors[] = {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 0.6f, 0.6f),
        glm::vec3(0.6f, 1.0f, 0.6f),
        glm::vec3(0.6f, 0.6f, 1.0f)
    };
    int totalColorsArraySize = sizeof(totalColors) / sizeof(glm::vec3);

    currentColor++;
    if (currentColor >= totalColorsArraySize)
    {
        currentColor = 0;
    }

    return totalColors[currentColor];
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
    float cubeVertices[] = {
        // POSITIONS            // COLORS           // TEXCOORDS
        // Front face
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f,   0.0f, 1.0f,

        // Back face
         0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,   1.0f, 1.0f,

        // Right face
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,   0.0f, 1.0f,

         // Left face
         -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
         -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,   1.0f, 1.0f,

         // Top face
          0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
          0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 0.0f,   0.0f, 0.0f,

         // Bottom face
          0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
          0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f,   0.0f, 1.0f
    };

    unsigned int indices[] = {
        // Front face
        0,  1,  2,
        0,  2,  3,

        // Back face
        4,  5,  6,
        4,  6,  7,

        // Right face
        8,  9,  10,
        8,  10, 11,

        // Left face
        12, 13, 14,
        12, 14, 15,

        // Top face
        16, 17, 18,
        17, 18, 19,

        // Bottom face
        20, 21, 22,
        21, 22, 23
    };

    // Triangle Texture Object
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Load the texture data
    int textureWidth;
    int textureHeight;
    int numOfColorChannels;
    stbi_set_flip_vertically_on_load(true);

    std::string imagePath = std::string(PROJECT_ROOT) + "/assets/textures/test_texture.png";
    unsigned char* data = stbi_load(imagePath.c_str(), &textureWidth, &textureHeight, &numOfColorChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Texture image data did not load successfully: " << imagePath << '\n';
    }

    // Free memory 
    stbi_image_free(data);

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Generate EBO to go into VAO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    Shader normalShader("default_vertex.glsl", "default_fragment.glsl");

    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // ===========================
    // Camera Setup
    //
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::vec3(cameraPos - cameraTarget);
    glm::vec3 cameraRight = glm::normalize(glm::cross(worldUp, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    // =============================
    // Scene Setup
    const float cubePositionConstant = 3;
    const glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(-cubePositionConstant, 0.0f, 0.0f),
        glm::vec3(-cubePositionConstant, 0.0f, -cubePositionConstant),
        glm::vec3(0.0f, 0.0f, -cubePositionConstant),
        glm::vec3(cubePositionConstant, 0.0f, 0.0f),
        glm::vec3(cubePositionConstant, 0.0f, cubePositionConstant),
        glm::vec3(0.0f, 0.0f, cubePositionConstant),
        glm::vec3(-cubePositionConstant, 0.0f, cubePositionConstant),
        glm::vec3(cubePositionConstant, 0.0f, -cubePositionConstant)
    };
    const int cubePositionsArrayLength = sizeof(cubePositions) / sizeof(glm::vec3) - 1;

    float timer = 0.0f;
    glm::vec3 currentScreenColor = switchScreenColor();

    // Main loop
    double lastTime = 0.0;
    while (!glfwWindowShouldClose(window)) {
        // =============================
        // Calculate Delta Time
        // 
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // =============================
        // Input
        //
        processInput(window);

        // =============================
        // Screen Color Timer
        //
        timer += deltaTime;

        std::cout << timer << '\n';

        if (timer >= 1.0f)
        {
            timer = 0.0f;
            currentScreenColor = switchScreenColor();
        }

        // =============================
        // Render
        //
        glClearColor(currentScreenColor.x, currentScreenColor.y, currentScreenColor.z, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // =============================
        // Collect Sine
        //
        float sineValue = sin(currentTime) * 100.0f;

        //std::cout << "Delta Time: " << deltaTime << '\n';

        // =============================
        // Active Default Shader
        //
        normalShader.use();

        // =============================
        // Camera Transformations
        // 
        // Rotate camera
        const float radius = 10.0f;
        float camX = sin(currentTime) * radius;
        float camZ = cos(currentTime) * radius;

        // =============================
        // Create Transformations
        // 


        // View Matrix
        glm::mat4 viewMatrix = glm::mat4(1.0f);
        viewMatrix = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        // Projection Matrix
        glm::mat4 projectionMatrix;
        projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        // Send matrices to the default shader

        int viewLoc = glGetUniformLocation(normalShader.Id, "sViewMatrix");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

        int projectionLoc = glGetUniformLocation(normalShader.Id, "sProjectionMatrix");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        // =============================
        // Setup Model Textures
        //
        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, texture);


        // =============================
        // Draw the objects
        // 
        // Bind the first bottom left triangle and draw it
        glBindVertexArray(VAO);

        for (int i = 0; i <= cubePositionsArrayLength; i++)
        {
            // Model Matrix
            glm::mat4 modelMatrix = glm::mat4(1.0f);

            modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
            modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f + sineValue), glm::vec3(1.0f, 0.0f, 0.0f));
            //modelMatrix = glm::rotate(modelMatrix, glm::radians(static_cast<float>(currentTime) * 100.0f), glm::vec3(1.0f, 0.0f, 1.0f));

            int modelLoc = glGetUniformLocation(normalShader.Id, "sModelMatrix");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            //glDrawArrays(GL_TRIANGLES, 0, 3);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        // =============================
        // Finish rendering
        // 
        // Swap the front buffer and back buffer
        glfwSwapBuffers(window);

        // =============================
        // Check for any events
        //
        glfwPollEvents();
    }

    // Cleanup and exit
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}