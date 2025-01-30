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

    unsigned int VBO;
    glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    // This part fucking sucks, IDK what to do, will think about it later

    const std::string* vertexShaderSource = readFile( vertex_shader_path );
    const char* vsrc = vertexShaderSource->c_str();
    unsigned int vertexShader;

    printf("%s", vsrc);

    vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &vsrc, nullptr );
    glCompileShader( vertexShader );
    delete vertexShaderSource;

    if ( !checkSuccess( vertexShader ) )
        return -1;


    const std::string* fragmentShaderSource = readFile( fragment_shader_path );
    const char* fsrc = fragmentShaderSource->c_str();
    unsigned int fragmentShader;

    fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &fsrc, nullptr );
    glCompileShader( fragmentShader );
    delete fragmentShaderSource;

    if ( !checkSuccess( fragmentShader ) )
        return -1;



    return 0;
}
