#include "window.h"

GLFWwindow* initWindow(
        int windowWidth,
        int windowHeight,
        const char* windowTitle
)
{
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

#ifdef __APPLE__
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
#endif

    GLFWwindow* window = glfwCreateWindow(
            windowWidth,
            windowHeight,
            windowTitle,
            nullptr,
            nullptr
    );
    if ( window == nullptr )
        return nullptr;

    glfwMakeContextCurrent( window );
    glfwSetFramebufferSizeCallback(window, [](auto window, auto width, auto height) {
        glViewport( 0, 0, width, height );
    });

    return window;
}

