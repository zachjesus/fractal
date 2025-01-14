#version 330 core

in vec2 FragCoord;

out vec4 FragColor;

uniform int maxIterations;
uniform float escapeRadius;

float escapeRadius2 = escapeRadius * escapeRadius;

uniform vec2 u_zoomCenter;
uniform float u_zoomSize;
uniform vec2 iResolution;

vec3 palette( in float t, in vec3 a, in vec3 b, in vec3 c, in vec3 d )
{
    return a + b*cos( 6.283185*(c*t+d) );
}

vec3 paletteColor(float t) {
    vec3 a = vec3(0.8, 0.5, 0.4);
    vec3 b = vec3(0.2, 0.4, 0.2);
    vec3 c = vec3(2.0, 1.0, 1.0	);
    vec3 d = vec3(0.0, 0.25, 0.25);
    return palette(fract(2.0*t + 0.5), a, b, c, d);
}

vec2 complexSquare(vec2 num) {
    return vec2(num.x*num.x - num.y*num.y, 2.0*num.x*num.y);
}

float mandleBrotSet(vec2 coords) {
    vec2 z = vec2(0.0, 0.0);
    int i;

    for(i = 0; i < maxIterations; i++) {
        z = complexSquare(z) + coords;
        if(dot(z, z) > escapeRadius2) break;
    }

    return i - log(log(dot(z, z)) / log(escapeRadius2)) / log(2.0);;     
}

void main() {
    vec2 scale = vec2(1.0 / 1.5, 1.0 / 2.0);
    vec2 uv = gl_FragCoord.xy - iResolution.xy * scale;
    uv *= 10.0 / min(3.0 * iResolution.x, 4.0 * iResolution.y);

    vec2 c = u_zoomCenter + (uv * 4.0 - vec2(2.0)) * (u_zoomSize / 4.0);
    
    float inSet = mandleBrotSet(c);
    vec3 finalColor = paletteColor(inSet/float(maxIterations));
    
    FragColor = vec4(finalColor, 1.0);
}