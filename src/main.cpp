#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a window (without an OpenGL context)
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Test Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll for and process events (e.g., window close, resize, etc.)
        glfwPollEvents();
    }

    // Cleanup and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}