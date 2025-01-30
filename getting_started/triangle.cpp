#include <glad/glad.h>
#include <iostream>

#include "triangle.h"
#include "../shared/window.h"
#include "../shared/shader.h"

float vertices[] = {
        0.6f,  0.7f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
};
unsigned int indices[] = {
        3, 0, 2,
        2, 0, 1
};
const char* vertexShaderPath = "../shaders/vertex.vert";
const char* fragmentShaderPath = "../shaders/fragment.frag";

int runT()
{
    if ( glfwInit() == GLFW_FALSE )
    {
        const char* errorMsg[1];
        glfwGetError( errorMsg );
        printf( "Error initializing glfw, %s", errorMsg[0] );

        return -1;
    }
    GLFWwindow* window = initWindow();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // This part fucking sucks, but not so much now

    unsigned int vertexShader = createShader( vertexShaderPath, GL_VERTEX_SHADER );
    if ( vertexShader == 0 ) return -1;

    unsigned int fragmentShader = createShader( fragmentShaderPath, GL_FRAGMENT_SHADER );
    if ( fragmentShader == 0 ) return -1;

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );

    if ( !checkProgramLinkingSuccess( shaderProgram ) )
        return -1;
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays (1, &VAO );
    glGenBuffers( 1, &VBO );
    glGenBuffers( 1, &EBO );

    glBindVertexArray(VAO);

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr );
    glEnableVertexAttribArray( 0 );

    glBindVertexArray( 0 );

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    while ( !glfwWindowShouldClose(window) )
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        glUseProgram( shaderProgram );
        glBindVertexArray( VAO );
        //glDrawArrays( GL_TRIANGLES, 0, 3 );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    return 0;
}
