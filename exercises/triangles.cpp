
#include "../shared/window.h"

int runExercise()
{
    if ( glfwInit() == GLFW_FALSE )
        return -1;

    GLFWwindow* window = initWindow();
    if ( window == nullptr )
        return -1;



    glfwTerminate();
    return 0;
}