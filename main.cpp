#include <GLFW/glfw3.h>
#include "lessons/getting_started/shaders/shaders.h"

int main() {
    if ( Shaders::run() < 0 )
    {
        glfwTerminate();
        return -1;
    }

    glfwTerminate();
    return 0;
}