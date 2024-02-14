#version 330 core
in vec3 vertClr;
out vec4 FragColor;

void main() {
    FragColor = vec4(vertClr, 1.0);
}
