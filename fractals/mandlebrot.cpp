#include <glad/glad.h>
#include "mandleBrot.h"
#include "../src/shaders.h"
#include <iostream>

static Shader& getShader() {
    static Shader localShader("../shaders/brot.vs", "../shaders/brot.fs");
    return localShader;
}

static float vertices[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f, 0.0f
};

static unsigned int VBO, VAO;

static int maxIterations;
static float escapeRadius;

void initMandleBrot(int iterations, float radius) {
    maxIterations = iterations;
    escapeRadius = radius;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void renderMandleBrot(glm::vec3 camera, float zoom) {
    Shader& ourShader = getShader();
    ourShader.use();
    ourShader.setInt("maxIterations", maxIterations);
    ourShader.setFloat("escapeRadius", escapeRadius);
    ourShader.setFloat("u_zoomSize", zoom);
    ourShader.setVec2("u_zoomCenter", glm::vec2(camera.x, camera.z));
    ourShader.setVec2("iResolution", glm::vec2(800, 600));
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);  
}