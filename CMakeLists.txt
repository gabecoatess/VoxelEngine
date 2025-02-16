cmake_minimum_required(VERSION 3.10)
project(VoxelEngine VERSION 0.1.0 LANGUAGES C CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add a compile definition for the project root
add_definitions(-DPROJECT_ROOT="${CMAKE_SOURCE_DIR}")

# Include directories
add_library(common_includes INTERFACE)
target_include_directories(common_includes INTERFACE
	${PROJECT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include
	${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
)

include(FetchContent)
FetchContent_Declare(
	imgui
	GIT_REPOSITORY https://github.com/ocornut/imgui.git
	GIT_TAG master
)
FetchContent_MakeAvailable(imgui)

add_library(imgui_lib STATIC
	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_tables.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui_lib PUBLIC 
	${imgui_SOURCE_DIR}
	${imgui_SOURCE_DIR}/backends
	${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include
)

# Subdirectory for external
add_subdirectory(external/glfw)

# Add GLAD as a library
add_library(glad
	external/glad/src/glad.c
	src/thirdparty/stb_image.cpp
	src/engine/MultiDimArray.cpp
	src/utilities/Renderer.cpp
	src/utilities/Mesh.cpp
	src/utilities/ResourceManager.cpp
	src/utilities/TimeUtility.cpp
	src/utilities/Shader.cpp
	src/world/Chunk.cpp
	src/objects/Camera.cpp
)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include)
target_link_libraries(glad PUBLIC common_includes)

# System Dependencies (OS provided)
find_package(OpenGL REQUIRED)

# Executable
add_executable(VoxelEngine
	src/main.cpp
	src/engine/MultiDimArray.cpp
	src/utilities/Renderer.cpp
	src/utilities/Mesh.cpp
	src/utilities/ResourceManager.cpp
	src/utilities/TimeUtility.cpp
	src/utilities/Shader.cpp
	src/thirdparty/stb_image.cpp
	src/world/Chunk.cpp
	src/objects/Camera.cpp
)
target_link_libraries(VoxelEngine PRIVATE common_includes glfw glad imgui_lib OpenGL::GL)