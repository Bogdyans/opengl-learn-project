#include "triangle.h"

#include "glad/glad.h"
#include <iostream>

#include "../../../shared/window.h"
#include "../../../lib/Shader.h"

namespace Triangle {
    float vertices[] = {
            0.6f, 0.7f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f, 0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {
            3, 0, 2,
            2, 0, 1
    };

    int run() {
        if (glfwInit() == GLFW_FALSE) {
            const char *errorMsg[1];
            glfwGetError(errorMsg);
            printf("Error initializing glfw, %s", errorMsg[0]);

            return -1;
        }
        GLFWwindow *window = initWindow();

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        // This part fucking sucks, but not so much now

        Shader shader(TRIANGLE_VERTEX_SHADER, TRIANGLE_FRAGMENT_SHADER);

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.use();
            glBindVertexArray(VAO);
            //glDrawArrays( GL_TRIANGLES, 0, 3 );
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteProgram(shader.id);

        return 0;
    }
}