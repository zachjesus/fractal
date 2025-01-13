#version 330 core

in vec2 FragCoord;

out vec4 FragColor;

uniform int maxIterations;
uniform float escapeRadius;

const vec2 escapeCenter = vec2(0.0, 0.0);
float escapeRadius2 = escapeRadius * escapeRadius;

uniform vec2 u_zoomCenter;
uniform float u_zoomSize;
uniform vec2 iResolution;

vec2 complexSquare(vec2 num) {
    return vec2(num.x*num.x - num.y*num.y, 2.0*num.x*num.y);
}

float mandleBrotSet(vec2 coords, out float minDist) {
    vec2 z = vec2(0.0, 0.0);
    int i;
    minDist = 1e20; 

    for(i = 0; i < maxIterations; i++) {
        z = complexSquare(z) + coords;
        if(dot(z, z) > escapeRadius2) break;

        float dist = length(z-escapeCenter);
        if(dist < minDist) {
            minDist = dist;
        }
    }

    return float(i) / float(maxIterations);
}

void main() {
    vec2 scale = vec2(1.0 / 1.5, 1.0 / 2.0);
    vec2 uv = gl_FragCoord.xy - iResolution.xy * scale;
    uv *= 10.0 / min(3.0 * iResolution.x, 4.0 * iResolution.y);

    vec2 z = vec2(0.0);
    vec2 c = u_zoomCenter + (uv * 4.0 - vec2(2.0)) * (u_zoomSize / 4.0);

    float minDist;
    float inSet = mandleBrotSet(c, minDist);
    if(inSet == 1.0) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        minDist = clamp(pow(minDist / 2.0, 0.8), 0.0, 1.0);
        vec3 color = mix(vec3(0.13, 0.3, .56), vec3(.58, 0.25, 0.16), minDist);
        FragColor = vec4(color, inSet);
    }
}