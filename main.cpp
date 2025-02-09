#include <GLFW/glfw3.h>
#include "lessons/getting_started/shaders/shaders.h"
#include "lessons/getting_started/textures/texture.h"

int main() {
    if ( textures::run() < 0 )
    {
        glfwTerminate();
        return -1;
    }

    glfwTerminate();
    return 0;
}