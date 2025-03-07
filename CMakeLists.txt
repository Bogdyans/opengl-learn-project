cmake_minimum_required(VERSION 3.28)
project(opengl_learn)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        "C:/Mine/work/gamedev/cpp/libs/glfw-3.4.bin.WIN64/include"
        "C:/Mine/work/gamedev/cpp/libs/glm/glm-1.0.0"
        external/glad/include
)

link_directories(
        "C:/Mine/work/gamedev/cpp/libs/glfw-3.4.bin.WIN64/lib-mingw-w64"
)

add_executable(
        opengl_learn main.cpp
        lessons/getting_started/first_window/first_window.cpp
        lessons/getting_started/first_window/first_window.h
        lessons/getting_started/first_triangle/triangle.h
        lessons/getting_started/first_triangle/triangle.cpp
        lessons/getting_started/first_triangle/triangle_tasks.cpp
        lessons/getting_started/first_triangle/triangle_tasks.h
        lessons/getting_started/shaders/shaders.h
        lessons/getting_started/shaders/shaders.cpp
        lessons/getting_started/textures/texture.cpp
        lessons/getting_started/coordinates/coordinates.cpp
        lessons/getting_started/coordinates/coordinates.h
)
add_library(
        glad external/glad/src/glad.c
        shared/files.h
        shared/files.cpp
        lib/Shader.cpp
        lib/Shader.h
        lib/Window.cpp
        lib/Window.h
        external/stb/stb_image.h
        external/stb/stb_image.cpp
)

find_package(OpenGL REQUIRED)

target_link_libraries(opengl_learn
        glad
        glfw3
        ${OPENGL_LIBRARIES}
)

