#include "shaders.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <valarray>

#include "../../../shared/window.h"
#include "../../../shared/files.h"
#include "../../../shared/shader.h"

int runS()
{
    if ( glfwInit() == GLFW_FALSE )
        return -1;

    GLFWwindow* window = initWindow();
    if ( window == nullptr )
        return -1;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int vertexShader, vertexShader2, fragmentShader, fragmentShader2;
    vertexShader = createShader( SHADERS_VERTEX_SHADER, GL_VERTEX_SHADER );
    fragmentShader = createShader( SHADERS_FRAGMENT_SHADER, GL_FRAGMENT_SHADER );
    vertexShader2 = createShader( SHADERS_VERTEX_SHADER2, GL_VERTEX_SHADER );
    fragmentShader2 = createShader( SHADERS_FRAGMENT_SHADER2, GL_FRAGMENT_SHADER );

    unsigned int shaderProgram, shaderProgram2;
    shaderProgram = glCreateProgram();
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );

    shaderProgram2 = glCreateProgram();
    glAttachShader( shaderProgram2, vertexShader2 );
    glAttachShader( shaderProgram2, fragmentShader2 );
    glLinkProgram( shaderProgram2 );


    if ( !checkProgramLinkingSuccess( shaderProgram ) || !checkProgramLinkingSuccess( shaderProgram2 ) )
        return -1;
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );
    glDeleteShader( vertexShader2 );
    glDeleteShader( fragmentShader2 );

    float vertices1[] = {
            -1.0f, -0.5f, 0.0f,
            -0.75f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
    };
    float vertices2[] = {
            //position                       color
            0.0f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
            0.8f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int VBO[2], VAO[2];
    glGenVertexArrays (2, VAO );
    glGenBuffers( 2, VBO );

    glBindVertexArray( VAO[0] );

    glBindBuffer( GL_ARRAY_BUFFER, VBO[0] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices1 ), vertices1, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr );
    glEnableVertexAttribArray( 0 );

    glBindVertexArray( VAO[1] );

    glBindBuffer( GL_ARRAY_BUFFER, VBO[1] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices2 ), vertices2, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)nullptr );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray( 0 );

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    while ( !glfwWindowShouldClose(window) )
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        glUseProgram( shaderProgram );

        float timeValue = glfwGetTime();
        float greenValue =  sin(timeValue) / 2.0  + 0.5f;
        int vertexColorLocation = glGetUniformLocation( shaderProgram, "ourColor" );
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray( VAO[0] );
        glDrawArrays( GL_TRIANGLES, 0, 3 );

        glUseProgram( shaderProgram2 );
        glBindVertexArray( VAO[1] );
        glDrawArrays( GL_TRIANGLES, 0, 3 );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgram2);

    return 0;
}