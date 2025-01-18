#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shaders/shaders.h"
#include "../fractals/mandleBrot.h"
#include <iostream>

//TODO
//Add ImGui for user input
//Burning ship fractal next.

glm::vec3 camera = glm::vec3(0.0f, 0.0f, 0.0f);
float zoom = .32f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.z += 0.002f;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.z -= 0.002f;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.x -= 0.002f;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.x += 0.002f;
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    zoom *= 1.02f; 
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    zoom /= 1.02f; 
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); this line is for MAC OS X

    GLFWwindow* window = glfwCreateWindow(800, 600, "Z-Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;  
    }    

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    initMandleBrot(100, 4, 
                glm::vec3(0.8, 0.5, 0.4), 
                glm::vec3(0.2, 0.3, 0.2), 
                glm::vec3(2.0, 1.0, 1.0), 
                glm::vec3(0.0, 0.25, 0.25), 0.5f, 9.0f);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

    while(!glfwWindowShouldClose(window))
    {
        processInput(window); 

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        renderMandleBrot(camera, zoom);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    cleanupMandleBrot();
    glfwTerminate();
    return 0;
}