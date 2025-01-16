#ifndef MANDLEBROT_H
#define MANDLEBROT_H

#include <glm/glm.hpp>

void initMandleBrot(int iterations, float radius, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, float scale, float freq);
void updateMandleBrot(int iterations, float radius, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, float scale, float freq);
void renderMandleBrot(glm::vec3 camera, float zoom);
void cleanupMandleBrot();

#endif