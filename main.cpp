#include <iostream>
#include <GLFW/glfw3.h>
#include "exercises/triangles.h"
#include "getting_started/firstWindow.h"

int main() {
    if ( runExercise( 1 ) < 0 )
    {
        glfwTerminate();
        return -1;
    }

    glfwTerminate();
    return 0;
}
