#include "Shader.h"

std::string* readFile( const char* filePath )
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

bool checkCompilationSuccess( unsigned int shader )
{
    int success;
    char infoLog[512];
    glGetShaderiv( shader, GL_COMPILE_STATUS, &success );

    if ( !success )
    {
        glGetShaderInfoLog( shader, 512, nullptr, infoLog );
        std::cout << shader << ": ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return success;
}

bool checkProgramLinkingSuccess( unsigned int program )
{
    int success;
    char infoLog[512];
    glGetProgramiv( program, GL_LINK_STATUS, &success );
    if( !success )
    {
        glGetProgramInfoLog( program, 512, nullptr, infoLog );
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    return success;
}

unsigned int createShader( const char* sSrc, int shaderType )
{
    unsigned int shader;

    shader = glCreateShader( shaderType );
    glShaderSource( shader, 1, &sSrc, nullptr );
    glCompileShader( shader );

    if ( !checkCompilationSuccess( shader ) )
        return 0;

    return shader;
}

void deleteShader( unsigned int shader )
{
    glDeleteShader( shader );
}

unsigned int createShaderProgram( unsigned int vShader, unsigned int fShader )
{
    unsigned int program = glCreateProgram();
    glAttachShader( program, vShader );
    glAttachShader( program, fShader );
    glLinkProgram( program );

    if ( !checkProgramLinkingSuccess(program) )
        return 0;

    return program;
}

Shader::Shader( const char* vertexPath, const char* fragmentPath )
{
    std::string* vShaderCode = readFile( vertexPath );
    std::string* fShaderCode = readFile( fragmentPath );

    unsigned int fShader, vShader;
    vShader = createShader( vShaderCode->c_str(), GL_VERTEX_SHADER );
    fShader = createShader( fShaderCode->c_str(), GL_FRAGMENT_SHADER );

    delete vShaderCode;
    delete fShaderCode;

    if ( !vShader || !fShader )
    {
        deleteShader( vShader );
        deleteShader( fShader );
        id = 0;
        return;
    }

    id = createShaderProgram( vShader, fShader );
    deleteShader( vShader );
    deleteShader( fShader );
}

void Shader::use() const
{
    glUseProgram( id );
}

void Shader::setBool( const std::string &name, bool value ) const
{
    glUniform1i( glGetUniformLocation( id, name.c_str() ), (int)value );
}
void Shader::setInt( const std::string &name, int value ) const
{
    glUniform1i( glGetUniformLocation( id, name.c_str() ), value );
}
void Shader::setFloat( const std::string &name, float value ) const
{
    glUniform1f( glGetUniformLocation( id, name.c_str() ), value );
}