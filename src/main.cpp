#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "render/ShaderProgram.h"
#include "resurses/resurceManager.h"
#include "render/Texture2D.h"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "render/sprite.h"

glm::ivec2 g_windowSize(640, 480);



int main(int argc, char** argv )
{
    if (!glfwInit())
    {
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "ugolki", NULL, NULL);
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
        ResurceManager reurceManager(argv[0]);
      
        auto pSpriteShaderProgram = reurceManager.loadShaderProgram("SpriteShaderBoard", "res/Shader/vSprite.txt", "res/Shader/fSprite.txt");
        if (!pSpriteShaderProgram)
        {
            std::cerr << "cant create shader progrram " << "DefoultSprite" << std::endl;
            return -1;
        }
        auto texBoard = reurceManager.loadTexture("BoardSTexture", "res/textures/Board.png");
        auto BoardSprite = reurceManager.loadSprite("NewSprite", "BoardSTexture", "SpriteShaderBoard", 640, 500);
        BoardSprite->setPosition(glm::vec2(5,-30));
        glm::mat4 projectMatrix = glm::ortho(0.f, static_cast<float>(g_windowSize.x), 0.f, static_cast<float>(g_windowSize.y), -100.f, 100.f);
        pSpriteShaderProgram->use();
        pSpriteShaderProgram->setInt("texBoard", 0);
        pSpriteShaderProgram->setmatrix4("projectionMat", projectMatrix);






        while (!glfwWindowShouldClose(pWindow))
        {
           //glClear(GL_COLOR_BUFFER_BIT);
            BoardSprite->render();

            glfwSwapBuffers(pWindow);

            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}