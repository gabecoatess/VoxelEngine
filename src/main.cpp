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
        // FRONT FACE (normal:  0,  0,  1)
        // Positions           // Colors           // TexCoords  // Normals
         0.5f,  0.5f,  0.5f,    1.0f,0.0f,0.0f,    1.0f,1.0f,   0.0f,0.0f,1.0f,
         0.5f, -0.5f,  0.5f,    0.0f,1.0f,0.0f,    1.0f,0.0f,   0.0f,0.0f,1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,0.0f,1.0f,    0.0f,0.0f,   0.0f,0.0f,1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,0.0f,0.0f,    0.0f,1.0f,   0.0f,0.0f,1.0f,

        // BACK FACE (normal: 0,  0, -1)
         0.5f,  0.5f, -0.5f,    1.0f,0.0f,0.0f,    0.0f,1.0f,   0.0f,0.0f,-1.0f,
         0.5f, -0.5f, -0.5f,    0.0f,1.0f,0.0f,    0.0f,0.0f,   0.0f,0.0f,-1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,0.0f,1.0f,    1.0f,0.0f,   0.0f,0.0f,-1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,0.0f,0.0f,    1.0f,1.0f,   0.0f,0.0f,-1.0f,

        // RIGHT FACE (normal: 1,  0, 0)
         0.5f,  0.5f,  0.5f,    1.0f,0.0f,0.0f,    1.0f,1.0f,   1.0f,0.0f,0.0f,
         0.5f, -0.5f,  0.5f,    0.0f,1.0f,0.0f,    1.0f,0.0f,   1.0f,0.0f,0.0f,
         0.5f, -0.5f, -0.5f,    0.0f,0.0f,1.0f,    0.0f,0.0f,   1.0f,0.0f,0.0f,
         0.5f,  0.5f, -0.5f,    0.0f,0.0f,0.0f,    0.0f,1.0f,   1.0f,0.0f,0.0f,

         // LEFT FACE (normal: -1,  0, 0)
         -0.5f,  0.5f,  0.5f,    1.0f,0.0f,0.0f,    0.0f,1.0f,  -1.0f,0.0f,0.0f,
         -0.5f, -0.5f,  0.5f,    0.0f,1.0f,0.0f,    0.0f,0.0f,  -1.0f,0.0f,0.0f,
         -0.5f, -0.5f, -0.5f,    0.0f,0.0f,1.0f,    1.0f,0.0f,  -1.0f,0.0f,0.0f,
         -0.5f,  0.5f, -0.5f,    0.0f,0.0f,0.0f,    1.0f,1.0f,  -1.0f,0.0f,0.0f,

         // TOP FACE (normal: 0,  1, 0)
          0.5f,  0.5f,  0.5f,    1.0f,0.0f,0.0f,    1.0f,1.0f,   0.0f,1.0f,0.0f,
         -0.5f,  0.5f,  0.5f,    0.0f,1.0f,0.0f,    0.0f,1.0f,   0.0f,1.0f,0.0f,
          0.5f,  0.5f, -0.5f,    0.0f,0.0f,1.0f,    1.0f,0.0f,   0.0f,1.0f,0.0f,
         -0.5f,  0.5f, -0.5f,    0.0f,0.0f,0.0f,    0.0f,0.0f,   0.0f,1.0f,0.0f,

         // BOTTOM FACE (normal: 0, -1, 0)
          0.5f, -0.5f,  0.5f,    1.0f,0.0f,0.0f,    1.0f,0.0f,   0.0f,-1.0f,0.0f,
         -0.5f, -0.5f,  0.5f,    0.0f,1.0f,0.0f,    0.0f,0.0f,   0.0f,-1.0f,0.0f,
          0.5f, -0.5f, -0.5f,    0.0f,0.0f,1.0f,    1.0f,1.0f,   0.0f,-1.0f,0.0f,
         -0.5f, -0.5f, -0.5f,    0.0f,0.0f,0.0f,    0.0f,1.0f,   0.0f,-1.0f,0.0f
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

    std::string imagePath = std::string(PROJECT_ROOT) + "/assets/textures/gabe_texture.png";
    unsigned char* data = stbi_load(imagePath.c_str(), & textureWidth, & textureHeight, & numOfColorChannels, 0);

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

    // Update position attribute (layout location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Update color attribute (layout location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Update texture coordinate attribute (layout location = 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Update normal attribute (layout location = 3)
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    // Generate EBO to go into VAO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    Shader normalShader("default_vertex.glsl", "default_fragment.glsl");

    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Multi-cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    float cubeRotations[] = {
        2,
        6,
        4,
        4,
        1,
        6,
        8,
        22,
        53,
        100,
    };
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // =============================
        // Input
        //
        processInput(window);

        // =============================
        // Render
        //
        glClearColor(7.0f, 0.6f, 0.6f, 0.0f);
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
        // Model Matrix
        /*
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        //modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f + sineValue), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f + (timeValue * 75.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f + (sineValue / 250.0f), 0.0f));
        */

        // View Matrix
        glm::mat4 viewMatrix = glm::mat4(1.0f);
        viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0));

        // Projection Matrix
        glm::mat4 projectionMatrix;
        projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        // Send matrices to the default shader
        /*
        int modelLoc = glGetUniformLocation(normalShader.Id, "sModelMatrix");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        */

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

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians((timeValue * 75.0f) * cubeRotations[i]), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::translate(model, glm::vec3((sineValue / 250.0f), 0.0f + (sineValue / 250.0f), 0.0f));

            normalShader.setMat4("sModelMatrix", model);

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        //glDrawArrays(GL_TRIANGLES, 0, 3);
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
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}