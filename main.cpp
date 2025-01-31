#include <iostream>
#include <GLFW/glfw3.h>
#include "lessons/getting_started/first_triangle/triangle_tasks.h"

int main() {
    if ( runET( TRIANGLE_TASK_1 ) < 0 )
    {
        glfwTerminate();
        return -1;
    }

    glfwTerminate();
    return 0;
}
