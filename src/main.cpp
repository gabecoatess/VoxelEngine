// main.cpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "utilities/ResourceManager.h"
#include "utilities/Mesh.h"
#include "utilities/Renderer.h"
#include "utilities/TimeUtility.h"
#include "utilities/Shader.h"
#include "objects/Camera.h"
#include "thirdparty/stb_image.h"

const int WIN_WIDTH = 1600;
const int WIN_HEIGHT = 900;
int currentWinWidth = WIN_WIDTH;
int currentWinHeight = WIN_HEIGHT;

TimeUtility& timeUtility = TimeUtility::GetInstance();

Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WIN_WIDTH * 0.5f;
float lastY = WIN_HEIGHT * 0.5f;
bool firstMouse = true;

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

    Renderer::GetCurrentCamera().ProcessMouseMovement(xoffset, yoffset);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    currentWinWidth = width;
    currentWinHeight = height;
    Renderer::SetViewport(currentWinWidth, currentWinHeight);
	Renderer::UpdateAllCamerasAspectRatio(currentWinWidth, currentWinHeight);
}
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
    Renderer::GetCurrentCamera().ProcessMouseScroll(static_cast<float>(yOffset));
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
	Camera& camera = Renderer::GetCurrentCamera();
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
    Renderer::Initialize(cam);
    timeUtility.Initialize();

    // Triangle data
    const std::vector<float> cubeVertices = {
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
    const std::vector<unsigned int> cubeIndices = {
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

    std::string imagePath = std::string(PROJECT_ROOT) + "/assets/textures/stone.png";
    unsigned char* data = stbi_load(imagePath.c_str(), &textureWidth, &textureHeight, &numOfColorChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "Texture image data did not load successfully: " << imagePath << '\n';
    }

    // Free memory 
    stbi_image_free(data);

    Shader* defaultShader = ResourceManager::LoadShader("default_vertex.glsl", "default_fragment.glsl", "default");

    cam.Initialize();

    Renderer::SetViewport(currentWinWidth, currentWinHeight);
	Renderer::UpdateAllCamerasAspectRatio(currentWinWidth, currentWinHeight);

    Mesh cubeMesh(cubeVertices, cubeIndices);
    Mesh cubeMesh2(cubeVertices, cubeIndices);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        timeUtility.Update();

        Renderer::ClearScreen(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

        float timeValue = glfwGetTime();
        float sineValue = sin(timeValue) * 100.0f;

        glBindTexture(GL_TEXTURE_2D, texture);
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        Renderer::DrawMesh(cubeMesh, *defaultShader, modelMatrix);

        // =============================
        // Finish rendering
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup and exit
    timeUtility.Destroy();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}