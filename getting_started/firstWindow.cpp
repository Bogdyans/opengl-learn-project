#include "glad/glad.h"
#include <cstdio>

#include "firstWindow.h"
#include "../shared/window.h"

void framebuffer_size_callback( GLFWwindow* window, int width, int height )
{
    glViewport( 0, 0, width, height );
}

void processInput( GLFWwindow* window )
{
    if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
        glfwSetWindowShouldClose( window, GLFW_TRUE );
}

int run()
{
    if ( glfwInit() == GLFW_FALSE )
    {
        const char* errorMsg[1];
        glfwGetError( errorMsg );
        printf( "Error initializing glfw, %s", errorMsg[0] );

        return -1;
    }

    GLFWwindow* window = initWindow();
    if ( window == nullptr )
    {
        printf( "Error creating window" );
        return -1;
    }
    glfwMakeContextCurrent( window );

    if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) )
    {
        printf( "Failed to initialize GLAD" );
        return -1;
    }

    //glViewport( 0, 0, 800, 600 );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    while ( !glfwWindowShouldClose( window ) )
    {
        processInput( window );

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT );

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    return 0;
}

