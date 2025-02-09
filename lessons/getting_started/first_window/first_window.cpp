#include "glad/glad.h"
#include <cstdio>

#include "first_window.h"
#include "../../../lib/Window.h"


namespace window
{
    static void processInput( GLFWwindow *window )
    {
        if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
            glfwSetWindowShouldClose( window, GLFW_TRUE );
    }

    int run()
    {
        if ( glfwInit() == GLFW_FALSE )
        {
            const char *errorMsg[1];
            glfwGetError( errorMsg );
            printf( "Error initializing glfw, %s", errorMsg[0] );

            return -1;
        }

        Window window = Window( 800, 600, "First Window" );
        if ( window.get() == nullptr )
        {
            printf( "Error creating window" );
            return -1;
        }

        if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) )
        {
            printf( "Failed to initialize GLAD" );
            return -1;
        }

        //glViewport( 0, 0, 800, 600 );
        window.setFramebufferSizeCallback(
                []( auto window, auto width, auto height ) -> void
                    {
                        glViewport( 0, 0, width, height );
                    });

        while ( !window.shouldClose() )
        {
            window.processInput( processInput );

            glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
            glClear( GL_COLOR_BUFFER_BIT );

            glfwSwapBuffers( window.get() );
            glfwPollEvents();
        }

        return 0;
    }
}