#include "Window.h"

Window::Window( int width, int height, const char *title )
{
    if ( !m_hinted )
    {
        windowHints();
        m_hinted = true;
    }

    m_instance = createWindow( width, height, title );
    if ( m_instance == nullptr )
        return;

    m_width = width;
    m_height = height;
    m_title = title;

    makeContextCurrent();
}

void Window::windowHints()
{
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

#ifdef __APPLE__
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
#endif
}

GLFWwindow* Window::createWindow( int width, int height, const char *title )
{
    return glfwCreateWindow(
            width,
            height,
            title,
            nullptr,
            nullptr
    );
}

void Window::setFramebufferSizeCallback( GLFWframebuffersizefun callback )
{
    glfwSetFramebufferSizeCallback( m_instance, callback );
}

void Window::makeContextCurrent()
{
    glfwMakeContextCurrent( m_instance );
}

void Window::processInput(void (*func)( GLFWwindow* )) {
    func( m_instance );
}