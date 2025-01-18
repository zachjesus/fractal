#ifndef MANDLEBROT_H
#define MANDLEBROT_H

#include <glm/glm.hpp>

void initMandelBrot(int iterations, float radius, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);
void updateMandelBrot(int iterations, float radius, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);
void renderMandelBrot(glm::vec3 camera, float zoom);
void cleanupMandelBrot();

#endif