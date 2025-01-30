#ifndef OPENGL_LEARN_WINDOW_H
#define OPENGL_LEARN_WINDOW_H

#include <GLFW/glfw3.h>

GLFWwindow* initWindow(
        int windowWidth = 800,
        int windowHeight = 600,
        const char* windowTitle = "Window"
);

#endif
