// main.cpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "utilities/TimeUtility.h"
#include "utilities/Shader.h"
#include "objects/Camera.h"
#include "thirdparty/stb_image.h"

// ===========================
// Window Settings
//
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 1280;
int currentWinWidth = WIN_WIDTH;
int currentWinHeight = WIN_HEIGHT;

// ===========================
// Service Setup
//
TimeUtility& timeUtility = TimeUtility::GetInstance();

// ===========================
// Object Setup
//
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WIN_WIDTH * 0.5f;
float lastY = WIN_HEIGHT * 0.5f;
bool firstMouse = true;

// ===========================
// Callbacks
//
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    currentWinWidth = width;
    currentWinHeight = height;
    glViewport(0, 0, currentWinWidth, currentWinHeight);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yOffset));
}

// ===========================
// Input
//
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
    // Movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, timeUtility.GetDeltaTime());
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, timeUtility.GetDeltaTime());
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, timeUtility.GetDeltaTime());
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, timeUtility.GetDeltaTime());
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(UP, timeUtility.GetDeltaTime());
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(DOWN, timeUtility.GetDeltaTime());
    }

    // Toggling Wireframe
    bool isFPressed = (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS);
    if (isFPressed && !fKeyPressed)
    {
        switchDrawMode();
    }

    fKeyPressed = isFPressed;

    // Exitting Application
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

// ===========================
// Main Game Startup
//
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
    GLFWwindow* window = glfwCreateWindow(currentWinWidth, currentWinHeight, "GLFW Test Window", nullptr, nullptr);
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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize Utilities
    timeUtility.Initialize();

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
        2,  1,  0,
        3,  2,  0,

        // Back face
        4,  5,  6,
        4,  6,  7,

        // Right face
        8,  9,  10,
        8,  10, 11,

        // Left face
        14, 13, 12,
        15, 14, 12,

        // Top face
        18, 17, 16,
        17, 18, 19,

        // Bottom face
        20, 21, 22,
        23, 22, 21
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

    glViewport(0, 0, currentWinWidth, currentWinHeight);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Enable face culling
    glEnable(GL_CULL_FACE);
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        timeUtility.Update();

        // =============================
        // Input
        //
        processInput(window);

        // =============================
        // Render
        //
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // =============================
        // Collect time
        //
        float timeValue = glfwGetTime();
        float sineValue = sin(timeValue) * 100.0f;

        // =============================
        // Active Default Shader
        //
        normalShader.use();

        // =============================
        // Create Transformations
        // 

        // Projection Matrix
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(currentWinWidth) / static_cast<float>(currentWinHeight), 0.1f, 100.0f);
        normalShader.setMat4("sProjectionMatrix", projectionMatrix);

        // View Matrix
        glm::mat4 viewMatrix = camera.GetViewMatrix();
        normalShader.setMat4("sViewMatrix", viewMatrix);

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

        // Model Matrix
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        normalShader.setMat4("sModelMatrix", modelMatrix);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

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
    timeUtility.Destroy();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}