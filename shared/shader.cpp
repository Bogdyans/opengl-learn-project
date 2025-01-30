
#include <string>
#include <iostream>
#include <fstream>

#include "glad/glad.h"

const std::string* readFile( const char* filePath )
{
    std::string line;
    auto text = new std::string();
    std::ifstream in( filePath );
    while( std::getline( in, line ) )
    {
        *text += line + "\n";
    }

    return text;
}

bool checkShaderCompilationSuccess( unsigned int shader )
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

unsigned int createShader(const char* shaderSource, int shaderType )
{
    const std::string* shaderSrcStr = readFile( shaderSource );
    const char* src = shaderSrcStr->c_str();

    //printf("%s\n", src);

    unsigned int shader;

    shader = glCreateShader( shaderType );
    glShaderSource( shader, 1, &src, nullptr );
    glCompileShader( shader );
    delete shaderSrcStr;

    if ( !checkShaderCompilationSuccess( shader ) )
        return 0;

    //printf("%d\n", shader);

    return shader;
}

bool checkProgramLinkingSuccess( unsigned int program )
{
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
    }

    return success;
}