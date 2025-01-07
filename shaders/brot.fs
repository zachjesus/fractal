#version 330 core

in vec2 FragCoord;

out vec4 FragColor;

uniform int maxIterations;

vec2 complexSquare(vec2 num) {
    return vec2(num.x * num.x - num.y * num.y, 2.0 * num.x * num.y);
}

float mandleBrotSet(vec2 coords) {
    vec2 z = vec2(0.0, 0.0);
    int i;
    for(i = 0; i < maxIterations; i++) {
        z = complexSquare(z) + coords;
        if(length(z) > 2.0) break;
    }
    return float(i) / float(maxIterations);
}

void main() {
    float inSet = mandleBrotSet(FragCoord);
    if(inSet == 1.0) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        FragColor = vec4(inSet, inSet, inSet, 1.0);
    }
}