#version 330 core

out vec4 FragColor;

uniform vec3 uColour;

void main() {
    FragColor = vec4(uColour, 1);
}