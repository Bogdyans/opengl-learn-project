cmake_minimum_required(VERSION 3.28)
project(opengl_learn)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        "C:/Mine/work/gamedev/cpp/libs/glfw-3.4.bin.WIN64/include"
        external/glad/include
)

link_directories(
        "C:/Mine/work/gamedev/cpp/libs/glfw-3.4.bin.WIN64/lib-mingw-w64"
        "C:/Mine/work/gamedev/cpp/libs/glew-2.1.0/lib/Release/x64"
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
)
add_library(
        glad external/glad/src/glad.c
        shared/files.h
        shared/files.cpp
        lib/Shader.cpp
        lib/Shader.h
        lib/Window.cpp
        lib/Window.h
)

find_package(OpenGL REQUIRED)

target_link_libraries(opengl_learn
        glad
        glfw3
        glew32
        ${OPENGL_LIBRARIES}
)

# Copy GLEW DLL to output directory
add_custom_command(TARGET opengl_learn POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Mine/work/gamedev/cpp//libs/glew-2.1.0/bin/Release/x64/glew32.dll"
        $<TARGET_FILE_DIR:opengl_learn>
)