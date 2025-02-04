#include "triangle_tasks.h"

#include "glad/glad.h"
#include <iostream>

#include "../../../lib/Window.h"
#include "../../../lib/Shader.h"

namespace TriangleTasks
{

    int run( TTasks task )
    {
        if ( glfwInit() == GLFW_FALSE )
            return -1;

        int result;
        switch (task)
        {
            case TRIANGLE_TASK_1 :
                result = taskT1();
                break;
            case TRIANGLE_TASK_2:
                result = taskT2();
                break;
            case TRIANGLE_TASK_3:
                result = taskT3();
                break;
        }

        glfwTerminate();
        return result;
    }

    int taskT1()
    {
        Window window = Window( 800, 600, "Task" ) ;
        if ( window.get() == nullptr )
            return -1;

        if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) )
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        Shader shader( TRIANGLE_VERTEX_SHADER, TRIANGLE_FRAGMENT_SHADER );

        float vertices[] = {
                -0.6f, 0.5f, 0.0f,
                -0.1f, -0.5f, 0.0f,
                -0.6f, -0.5f, 0.0f,

                0.1f, 0.5f, 0.0f,
                0.6f, -0.5f, 0.0f,
                0.1f, -0.5f, 0.0f
        };

        unsigned int VAO, VBO;
        glGenVertexArrays( 1, &VAO );
        glGenBuffers( 1, &VBO );

        glBindVertexArray( VAO );

        glBindBuffer( GL_ARRAY_BUFFER, VBO );
        glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr );
        glEnableVertexAttribArray( 0 );

        glBindVertexArray( 0 );

        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        while ( !window.shouldClose() )
        {
            glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
            glClear( GL_COLOR_BUFFER_BIT );

            shader.use();
            glBindVertexArray( VAO );
            glDrawArrays( GL_TRIANGLES, 0, 6 );

            glfwSwapBuffers( window.get() );
            glfwPollEvents();
        }

        glDeleteVertexArrays( 1, &VAO );
        glDeleteBuffers( 1, &VBO );
        glDeleteProgram( shader.id );

        return 0;
    }

    int taskT2()
    {
        Window window = Window( 800, 600, "Task2" );
        if ( window.get() == nullptr )
            return -1;

        if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) )
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        Shader shader( TRIANGLE_VERTEX_SHADER, TRIANGLE_VERTEX_SHADER );

        float vertices1[] = {
                -0.6f, 0.5f, 0.0f,
                -0.1f, -0.5f, 0.0f,
                -0.6f, -0.5f, 0.0f,
        };

        float vertices2[] = {
                0.1f, 0.5f, 0.0f,
                0.6f, -0.5f, 0.0f,
                0.1f, -0.5f, 0.0f
        };

        unsigned int VAO[2], VBO[2];
        glGenVertexArrays( 2, VAO );
        glGenBuffers( 2, VBO );

        glBindVertexArray( VAO[0] );
        glBindBuffer( GL_ARRAY_BUFFER, VBO[0] );
        glBufferData( GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr );
        glEnableVertexAttribArray( 0 );

        glBindVertexArray( VAO[1] );
        glBindBuffer( GL_ARRAY_BUFFER, VBO[1] );
        glBufferData( GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr );
        glEnableVertexAttribArray( 0 );

        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        while ( !window.shouldClose() )
        {
            glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
            glClear( GL_COLOR_BUFFER_BIT );

            shader.use();
            glBindVertexArray( VAO[0] );
            glDrawArrays( GL_TRIANGLES, 0, 3 );

            glBindVertexArray( VAO[1] );
            glDrawArrays( GL_TRIANGLES, 0, 3 );

            glfwSwapBuffers( window.get() );
            glfwPollEvents();
        }

        glDeleteProgram( shader.id );
        glDeleteBuffers( 2, VBO );
        glDeleteVertexArrays( 2, VAO );

        return 0;
    }

    int taskT3()
    {
        Window window = Window( 800, 600, "Task3" );
        if ( window.get() == nullptr )
            return -1;

        if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) )
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        Shader shader( TRIANGLE_VERTEX_SHADER, TRIANGLE_FRAGMENT_SHADER );
        Shader shader2( TRIANGLE_VERTEX_SHADER, TRIANGLE_FRAGMENT_SHADER2 );

        float vertices1[] = {
                -0.6f, 0.5f, 0.0f,
                -0.1f, -0.5f, 0.0f,
                -0.6f, -0.5f, 0.0f,
        };

        float vertices2[] = {
                0.1f, 0.5f, 0.0f,
                0.6f, -0.5f, 0.0f,
                0.1f, -0.5f, 0.0f
        };

        unsigned int VAO[2], VBO[2];
        glGenVertexArrays( 2, VAO );
        glGenBuffers( 2, VBO );

        glBindVertexArray( VAO[0] );
        glBindBuffer( GL_ARRAY_BUFFER, VBO[0] );
        glBufferData( GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr );
        glEnableVertexAttribArray( 0 );

        glBindVertexArray( VAO[1] );
        glBindBuffer( GL_ARRAY_BUFFER, VBO[1] );
        glBufferData( GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr );
        glEnableVertexAttribArray( 0 );

        //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        while ( !window.shouldClose() )
        {
            glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
            glClear( GL_COLOR_BUFFER_BIT );

            shader.use();
            glBindVertexArray( VAO[0] );
            glDrawArrays( GL_TRIANGLES, 0, 3 );

            shader2.use();
            glBindVertexArray( VAO[1] );
            glDrawArrays( GL_TRIANGLES, 0, 3 );

            glfwSwapBuffers( window.get() );
            glfwPollEvents();
        }

        glDeleteProgram( shader.id );
        glDeleteProgram( shader2.id );
        glDeleteBuffers( 2, VBO );
        glDeleteVertexArrays( 2, VAO );

        return 0;
    }
}