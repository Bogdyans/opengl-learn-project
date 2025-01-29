#include <iostream>
#include <GLFW/glfw3.h>
#include "getting_started/triangle.h"

int main() {
    if ( runT() < 0 )
    {
        glfwTerminate();
        return -1;
    }


    glfwTerminate();
    return 0;
}
