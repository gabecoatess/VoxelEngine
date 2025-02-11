#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Temporary Vertex Program
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 data;\n"
"out vec3 datas;\n"
"void main()\n"
"{\n"
"   datas = data;\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Temporary Fragment Program
const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 datas;\n"
"out vec4 FragColor;\n\n"
"void main()\n"
"{\n"
"   FragColor = vec4(datas.x, datas.y, datas.z, 1.0);\n"
"}\0";

// Temporary Fragment Program Yellow
const char* fragmentShaderYellowSource = "#version 330 core\n"
"in vec3 datas;\n"
"out vec4 FragColor;\n\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0, 1.0, 0.0, 1.0);\n"
"}\0";

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

    // Configure the shader
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int fragmentYellowShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    fragmentYellowShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glShaderSource(fragmentYellowShader, 1, &fragmentShaderYellowSource, NULL);
    glCompileShader(fragmentYellowShader);

    // Error checking for vertex shader
    int successV;
    char infoLogV[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successV);

    if (!successV)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLogV);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogV << "\n";
    }

    // Error checking for fragment shader
    int successF;
    char infoLogF[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successF);

    if (!successF)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogF);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogF << "\n";
    }

    // Error checking for fragment yellow shader
    int successFY;
    char infoLogFY[512];
    glGetShaderiv(fragmentYellowShader, GL_COMPILE_STATUS, &successFY);

    if (!successFY)
    {
        glGetShaderInfoLog(fragmentYellowShader, 512, NULL, infoLogFY);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogFY << "\n";
    }

    // Create shader program
    unsigned int shaderProgram;
    unsigned int yellowShaderProgram;
    shaderProgram = glCreateProgram();
    yellowShaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glAttachShader(yellowShaderProgram, vertexShader);
    glAttachShader(yellowShaderProgram, fragmentYellowShader);

    glLinkProgram(shaderProgram);
    glLinkProgram(yellowShaderProgram);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
            
        processInput(window);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(yellowShaderProgram);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup and exit
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}