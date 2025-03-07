#include "coordinates.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "../../../lib/Window.h"

namespace coordinates
{
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    int run()
    {
        if ( glfwInit() == GLFW_FALSE )
            return -1;

        auto window = Window( WINDOW_WIDTH, WINDOW_HEIGHT, "Coordinates" );
        if ( !window.get() )
            return -1;

        if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) )
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        window.setFramebufferSizeCallback(
                []( auto window, auto width, auto height ) -> void
                {
                    glViewport( 0, 0, width, height );
                });

        while ( !window.shouldClose() )
        {

            glfwSwapBuffers( window.get() );
            glfwPollEvents();
        }

        glfwTerminate();

        return 0;
    }
}
