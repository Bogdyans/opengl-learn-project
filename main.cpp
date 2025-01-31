#include <GLFW/glfw3.h>
#include "lessons/getting_started/shaders/shaders.h"

int main() {
    if ( runS() < 0 )
    {
        glfwTerminate();
        return -1;
    }

    glfwTerminate();
    return 0;
}
