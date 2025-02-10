cmake_minimum_required(VERSION 3.10)
project(VoxelEngine VERSION 0.1.0 LANGUAGES C CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Subdirectory for external
add_subdirectory(external/glfw)

# Add GLAD as a library
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include)

# System Dependencies (OS provided)
find_package(OpenGL REQUIRED)

# Executable
add_executable(VoxelEngine src/main.cpp)

target_link_libraries(VoxelEngine PRIVATE glfw glad OpenGL::GL)