#include <glad/glad.h>
#include "mandleBrot.h"
#include "shaders.h"

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

static int max;

void initMandleBrot(int maxIterations) {
    max = maxIterations;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void renderMandleBrot() {
    Shader& ourShader = getShader();
    ourShader.use();
    ourShader.setInt("maxIterations", max);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);  
}