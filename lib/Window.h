//
// Created by Bogdya on 04.02.2025.
//

#ifndef OL_WINDOW_H
#define OL_WINDOW_H

#include <GLFW/glfw3.h>

class Window {

private:
    GLFWwindow* m_instance;

    int m_width;
    int m_height;
    const char* m_title;

    bool m_hinted = false;

    static void windowHints();
    static GLFWwindow* createWindow( int width, int height, const char *title );
    void makeContextCurrent();

public:
    Window( int width, int height, const char* title );

    void close() { glfwSetWindowShouldClose( m_instance, GLFW_TRUE ); }
    void processInput( void (* func)( GLFWwindow* ) );

    void setFramebufferSizeCallback( GLFWframebuffersizefun callback );

    [[nodiscard]] bool shouldClose() const { return glfwWindowShouldClose( m_instance ); }
    [[nodiscard]] GLFWwindow* get() const { return m_instance; }
    [[nodiscard]] int getWidth() const { return m_width; }
    [[nodiscard]] int getHeight() const { return m_height; }
    [[nodiscard]] const char* getTitle() const { return m_title; }
};


#endif //OL_WINDOW_H
