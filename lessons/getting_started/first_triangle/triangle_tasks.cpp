#include "triangle_tasks.h"

#include "glad/glad.h"
#include <iostream>

#include "../../../shared/window.h"
#include "../../../shared/shader.h"


int runET( TTasks task )
{
    int result;
    switch (task){
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


    return result;
}

int taskT1()
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

    unsigned int vertexShader, fragmentShader;
    vertexShader = createShader( TRIANGLE_VERTEX_SHADER, GL_VERTEX_SHADER );
    fragmentShader = createShader( TRIANGLE_FRAGMENT_SHADER, GL_FRAGMENT_SHADER );

    if ( !vertexShader || !fragmentShader )
    {
        std::cout << "Failed to compile shaders" << std::endl;
        return -1;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );

    if ( !checkProgramLinkingSuccess( shaderProgram ) )
        return -1;

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

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
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr );
    glEnableVertexAttribArray( 0 );

    glBindVertexArray( 0 );

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    while ( !glfwWindowShouldClose( window ) )
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        glUseProgram( shaderProgram );
        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 6 );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

int taskT2()
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

    unsigned int vertexShader, fragmentShader;
    vertexShader = createShader( TRIANGLE_VERTEX_SHADER, GL_VERTEX_SHADER );
    fragmentShader = createShader( TRIANGLE_FRAGMENT_SHADER, GL_FRAGMENT_SHADER );

    if ( !vertexShader || !fragmentShader )
    {
        std::cout << "Failed to compile shaders" << std::endl;
        return -1;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );

    if ( !checkProgramLinkingSuccess( shaderProgram ) )
        return -1;
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

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
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices1 ), vertices1, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr );
    glEnableVertexAttribArray( 0 );

    glBindVertexArray( VAO[1] );
    glBindBuffer( GL_ARRAY_BUFFER, VBO[1] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices2 ), vertices2, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr );
    glEnableVertexAttribArray( 0 );

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    while ( !glfwWindowShouldClose( window ) )
    {
        glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        glUseProgram( shaderProgram );
        glBindVertexArray( VAO[0] );
        glDrawArrays( GL_TRIANGLES, 0, 3 );

        glBindVertexArray( VAO[1] );
        glDrawArrays( GL_TRIANGLES, 0, 3 );

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    glDeleteProgram( shaderProgram );
    glDeleteBuffers( 2, VBO );
    glDeleteVertexArrays( 2, VAO );

    glfwTerminate();
    return 0;
}

int taskT3()
{
    return 0;
}