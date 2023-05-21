#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "render/ShaderProgram.h"
#include "resurses/resurceManager.h"
GLfloat point[] = {
    0.0f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};



int main(int argc, char** argv )
{
  
    GLFWwindow* pWindow;

    if (!glfwInit())
    {
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    pWindow = glfwCreateWindow(640, 480, "Batlle city", NULL, NULL);
    if (!pWindow)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "cant init glad" << std::endl;
        return -1;
    }
    std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;

    glClearColor(1, 1, 0, 1);

   
    {
        ReurceManager reurceManager(argv[0]);
        auto pDefoultShaderProgram = reurceManager.loadShaderProgram("DefoultShader", "res/Shader/vertex.txt", "res/Shader/fragment.txt");
        if (!pDefoultShaderProgram)
        {
            std::cerr << "cant create shader progrram " << "DefoultShader" << std::endl;
            return -1;
        }

        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        while (!glfwWindowShouldClose(pWindow))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            pDefoultShaderProgram->use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(pWindow);

            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}