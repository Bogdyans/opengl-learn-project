#include "texture.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../../external/stb/stb_image.h"

#include "../../../lib/Window.h"
#include "../../../shared/files.h"
#include "../../../lib/Shader.h"

namespace textures
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

        Window window = Window( 800, 600, "Textures" );
        if ( !window.get() )
            return -1;

        if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) )
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        window.setFramebufferSizeCallback(
                []( auto window, auto width, auto height) -> void
                {
                    glViewport( 0, 0, width, height );
                });

        Shader shader( TEXTURES_VERTEX_SHADER, TEXTURES_FRAGMENT_SHADER );

        float vertices[] = {
                // positions                           // colors                            // texture coords
                0.5f,  0.5f,   0.0f,      1.0f, 0.0f,   0.0f,      1.0f,  1.0f,   // top right
                0.5f,  -0.5f, 0.0f,      0.0f, 1.0f,  0.0f,     1.0f, 0.0f,   // bottom right
                -0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f,     0.0f, 0.0f,   // bottom left
                -0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 0.0f,     0.0f, 1.0f    // top left
        };
        unsigned int indices[] = {
                3, 1, 2,
                3, 0, 1
        };
        unsigned int VAO, VBO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        unsigned int texture, texture1;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char *data = stbi_load( "C:/Mine/work/programming/projects/C++/opengl-learn/files/textures/wooden_container.png", &width, &height, &nrChannels, 0);
        if ( data )
        {
            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
            glGenerateMipmap( GL_TEXTURE_2D );
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free( data );

        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load image, create texture and generate mipmaps
        int width1, height1, nrChannels1;
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char *data1 = stbi_load( "C:/Mine/work/programming/projects/C++/opengl-learn/files/textures/ustal.jpg", &width1, &height1, &nrChannels1, 0);
        if ( data1 )
        {
            std::cout << nrChannels;
            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1 );
            glGenerateMipmap( GL_TEXTURE_2D );
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(  data1 );

        shader.use();
        shader.setInt( "ourTexture", 0 );
        shader.setInt( "otherTexture", 1 );


        while ( !window.shouldClose() )
        {
            window.processInput( processInput );

            glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
            glClear( GL_COLOR_BUFFER_BIT );

            glActiveTexture( GL_TEXTURE0 );
            glBindTexture( GL_TEXTURE_2D, texture );
            glActiveTexture( GL_TEXTURE1 );
            glBindTexture( GL_TEXTURE_2D, texture1 );

            // render container
            shader.use();

            int vertexOffsetLocation = glGetUniformLocation( shader.id, "offset" );
            glUniform2f( vertexOffsetLocation, velocity[0], velocity[1] );
            glBindVertexArray( VAO );
            glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );


            glfwSwapBuffers( window.get() );
            glfwPollEvents();
        }


        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        glfwTerminate();
        return 0;
    }

}