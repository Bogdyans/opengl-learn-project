//
// Created by Bogdya on 04.02.2025.
//

#ifndef OL_WINDOW_H
#define OL_WINDOW_H

#include <GLFW/glfw3.h>

class Window {

private:
    GLFWwindow* instance;

    int width;
    int height;
    const char* title;

public:
    Window( int width, int height, const char* title );

    [[nodiscard]] GLFWwindow* get() const { return instance; };
    [[nodiscard]] int getWidth() const { return width; }
    [[nodiscard]] int getHeight() const { return height; }
    [[nodiscard]] const char* getTitle() const { return title; }
};


#endif //OL_WINDOW_H
