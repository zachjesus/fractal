#include <glad/glad.h>
#include "mandelBrot.h"
#include "../shaders/shaders.h"
#include <glm/glm.hpp>
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

int maxIterations;
float escapeRadius;
glm::vec3 aColor, bColor, CColor, dColor;

void initMandelBrot(int iterations, float radius, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d) {
    maxIterations = iterations;
    escapeRadius = radius;
    aColor = a;
    bColor = b;
    CColor = c;
    dColor = d;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void updateMandelBrot(int iterations, float radius, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d) {
    maxIterations = iterations;
    escapeRadius = radius;
    aColor = a;
    bColor = b;
    CColor = c;
    dColor = d;
}

void renderMandelBrot(glm::vec3 camera, float zoom) {
    Shader& ourShader = getShader();
    ourShader.use();
    ourShader.setInt("maxIterations", maxIterations);
    ourShader.setFloat("escapeRadius", escapeRadius);
    ourShader.setFloat("u_zoomSize", zoom);
    ourShader.setVec2("u_zoomCenter", glm::vec2(camera.x, camera.z));
    ourShader.setVec2("iResolution", glm::vec2(800, 600));
    ourShader.setVec3("aColor", aColor);
    ourShader.setVec3("bColor", bColor);
    ourShader.setVec3("cColor", CColor);
    ourShader.setVec3("dColor", dColor);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);  
}

void cleanupMandelBrot() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}