#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>

#include "triangle.h"

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;
float vertices[] ={
        -0.5f, -0.5f, 0.0f,
         0.2f, 0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
};
const char* vertex_shader_path = "../shaders/vertex.vert";
const char* fragment_shader_path = "../shaders/fragment.frag";

GLFWwindow* initWindow()
{
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 4 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

#ifdef __APPLE__
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
#endif

    GLFWwindow* window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "First Window", nullptr, nullptr );
    if ( window == nullptr )
        return nullptr;

    glfwMakeContextCurrent( window );
    glfwSetFramebufferSizeCallback(window, [](auto window, auto width, auto height) {
        glViewport( 0, 0, width, height );
    });

    return window;
}

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

unsigned int createShader( const char* shaderSource, int shaderType )
{
    const std::string* shaderSrcStr = readFile( shaderSource );
    const char* src = shaderSrcStr->c_str();
    unsigned int shader;

    shader = glCreateShader( shaderType );
    glShaderSource( shader, 1, &src, nullptr );
    glCompileShader( shader );
    delete shaderSrcStr;

    if ( !checkShaderCompilationSuccess( shader ) )
        return 0;

    return shader;
}

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

    unsigned int vertexShader = createShader( vertex_shader_path, GL_VERTEX_SHADER );
    if ( vertexShader == 0 ) return -1;

    unsigned int fragmentShader = createShader( fragment_shader_path, GL_FRAGMENT_SHADER );
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

    unsigned int VBO;
    glGenBuffers( 1, &VBO );
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr );
    glEnableVertexAttribArray( 0 );

    glBindVertexArray( 0 );

    while ( !glfwWindowShouldClose(window) )
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        glUseProgram( shaderProgram );
        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 3 );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    return 0;
}
