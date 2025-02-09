#include "shaders.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <valarray>

#include "../../../lib/Window.h"
#include "../../../shared/files.h"
#include "../../../lib/Shader.h"


namespace shaders
{

    float velocity[] = { 0.0f, 0.0f };

    static void processInput( GLFWwindow *window )
    {
        if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
            glfwSetWindowShouldClose( window, GLFW_TRUE );

        if ( glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS )
            velocity[1] = 0.008;
        else if ( glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS )
            velocity[1] = -0.008;
        else
            velocity[1] = 0;

        if ( glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS )
            velocity[0] = 0.008;
        else if ( glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS )
            velocity[0] = -0.008;
        else
            velocity[0] = 0;

    }


    int run()
    {
        if ( glfwInit() == GLFW_FALSE )
            return -1;

        Window window = Window( 800, 600, "Shaders" );
        if ( window.get() == nullptr )
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

        Shader shaderProgram( SHADERS_VERTEX_SHADER, SHADERS_FRAGMENT_SHADER );
        Shader shaderProgram2( SHADERS_VERTEX_SHADER2, SHADERS_FRAGMENT_SHADER2 );

        if ( !shaderProgram.id || !shaderProgram2.id )
            return -1;

        float vertices1[] = {
                -1.0f, -0.5f, 0.0f,
                -0.75f, 0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f
        };
        float vertices2[] = {
                //position                       color
                0.0f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
                -0.3f, -0.3f, 0.0f, 0.0f, 1.0f, 0.0f,
                0.3f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f
        };

        unsigned int VBO[2], VAO[2];
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

        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) ( 3 * sizeof(float) ) );
        glEnableVertexAttribArray( 1 );

        glBindVertexArray( 0 );

        //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        float offset[] = {
                0.0f, 0.0f, 0.0f
        };

        while ( !window.shouldClose() ) {
            window.processInput( processInput );

            glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
            glClear( GL_COLOR_BUFFER_BIT );

            shaderProgram.use();

            float timeValue = glfwGetTime();
            float greenValue = sin(timeValue) / 2.0 + 0.5f;
            int vertexColorLocation = glGetUniformLocation( shaderProgram.id, "ourColor" );
            glUniform4f( vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f );

            int vertexOffsetLocation = glGetUniformLocation( shaderProgram.id, "offset" );
            glUniform3f( vertexOffsetLocation, offset[0], offset[1], offset[2] );
            glBindVertexArray( VAO[0] );
            glDrawArrays( GL_TRIANGLES, 0, 3 );


            shaderProgram2.use();

            int vertexOffsetLocation2 = glGetUniformLocation( shaderProgram2.id, "offset" );
            glUniform3f( vertexOffsetLocation2, offset[0], offset[1], offset[2] );
            glBindVertexArray( VAO[1] );
            glDrawArrays( GL_TRIANGLES, 0, 3 );

            offset[0] += velocity[0];
            offset[1] += velocity[1];

            glfwSwapBuffers( window.get() );
            glfwPollEvents();
        }

        glDeleteVertexArrays( 2, VAO );
        glDeleteBuffers( 2, VBO );
        glDeleteProgram( shaderProgram.id );
        glDeleteProgram( shaderProgram2.id );

        return 0;
    }
}