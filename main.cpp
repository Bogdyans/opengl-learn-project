#include <GLFW/glfw3.h>
#include "lessons/getting_started/shaders/shaders.h"
#include "lessons/getting_started/textures/texture.h"
#include "lessons/getting_started/coordinates/coordinates.h"

int main() {
    if ( coordinates::run() < 0 )
    {
        glfwTerminate();
        return -1;
    }

    glfwTerminate();
    return 0;
}