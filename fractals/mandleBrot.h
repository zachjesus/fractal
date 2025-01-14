#ifndef MANDLEBROT_H
#define MANDLEBROT_H

#include <glm/glm.hpp>

void initMandleBrot(int maxIterations, float radius);
void renderMandleBrot(glm::vec3 camera, float zoom);

#endif