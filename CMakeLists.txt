cmake_minimum_required(VERSION 3.10)
project(VoxelEngine VERSION 0.1.0 LANGUAGES C CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define project directory
add_definitions(-DPROJECT_ROOT="${CMAKE_SOURCE_DIR}")

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Subdirectory for external
add_subdirectory(external/glfw)

# Add GLAD as a library
add_library(glad external/glad/src/glad.c "src/utilities/Shader.h" "src/utilities/Shader.cpp" "src/thirdparty/stb_image.h" "src/thirdparty/stb_image.cpp")
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include)

# System Dependencies (OS provided)
find_package(OpenGL REQUIRED)

# Executable
add_executable(VoxelEngine src/main.cpp "src/utilities/Shader.h" "src/utilities/Shader.cpp" "src/thirdparty/stb_image.h" "src/thirdparty/stb_image.cpp")

target_link_libraries(VoxelEngine PRIVATE glfw glad OpenGL::GL)