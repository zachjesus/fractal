#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../shaders/shaders.h"
#include "../fractals/mandelBrot.h"
#include <iostream>

float cameraSpeed = 0.002f;
float zoomSpeed = 1.02f;
glm::vec3 camera = glm::vec3(0.0f, 0.0f, 0.0f);
float zoom = .32f;

int iterations = 100;
float radius = 4.0f;
glm::vec3 a = glm::vec3(0.8f, 0.5f, 0.4f);
glm::vec3 b = glm::vec3(0.2f, 0.3f, 0.2f);
glm::vec3 c = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 d = glm::vec3(0.0f, 0.25f, 0.25f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.z += cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.z -= cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.x -= cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.x += cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        zoom *= zoomSpeed;
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        zoom /= zoomSpeed;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Z-Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;  
    }    

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //Enable Keyboard Controls
    
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330"); 
    
    initMandelBrot(100, 4, 
                glm::vec3(0.8, 0.5, 0.4), 
                glm::vec3(0.2, 0.3, 0.2), 
                glm::vec3(2.0, 1.0, 1.0), 
                glm::vec3(0.0, 0.25, 0.25));
    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window); 

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Mandelbrot Settings");
        ImGui::SliderInt("Fractal Iterations", &iterations, 0, 300);
        ImGui::SliderFloat("Escape Radius", &radius, 1.0f, 8.0f);
        ImGui::ColorEdit3("Color A", (float*)&a);
        ImGui::ColorEdit3("Color B", (float*)&b);
        ImGui::ColorEdit3("Color C", (float*)&c);
        ImGui::ColorEdit3("Color D", (float*)&d);
        ImGui::SliderFloat("Camera Speed", &cameraSpeed, 0.00001f, 0.01f);
        ImGui::SliderFloat("Zoom Speed", &zoomSpeed, 1.001f, 1.1f);
        if (ImGui::Button("Update Mandelbrot"))
        {
            updateMandelBrot(iterations, radius, a, b, c, d);
        }
        ImGui::End();
        ImGui::Render();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        renderMandelBrot(camera, zoom);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    cleanupMandelBrot();
    glfwTerminate();
    return 0;
}