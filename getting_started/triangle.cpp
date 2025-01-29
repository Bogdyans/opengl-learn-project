#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include "triangle.h"


float vertices[] ={
        -0.5f, -0.5f, 0.0f,
         0.2f, 0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
};
const char* vertex_shader_path = "../shaders/vertex.vert";
const char* fragment_shader_path = "../shaders/fragment.frag";

const char* readFile( const char* filePath )
{
    std::ifstream file( filePath );
    if ( !file.is_open() ) {
        std::cout << "Failed to open file: " << filePath << std::endl;
        return nullptr;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str().c_str();
}

bool checkSuccess( unsigned int shader )
{
    int success;
    char infoLog[512];
    glGetShaderiv( shader, GL_COMPILE_STATUS, &success );

    if ( !success )
    {
        glGetShaderInfoLog( shader, 512, nullptr, infoLog );
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return success;
}

int runT()
{
    unsigned int VBO;
    glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    const char* vertexShaderSource = readFile( vertex_shader_path );
    unsigned int vertexShader;

    vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &vertexShaderSource, nullptr );
    glCompileShader( vertexShader );

    if ( !checkSuccess( vertexShader ) )
        return -1;




    const char* fragmentShaderSource = readFile( fragment_shader_path );
    unsigned int fragmentShader;

    fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &fragmentShaderSource, nullptr );
    glCompileShader( fragmentShader );

    if ( !checkSuccess( fragmentShader ) )
        return -1;



    return 0;
}
