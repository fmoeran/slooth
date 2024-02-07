#version 330 core

layout (location=0) in vec3 pos;
layout (location=1) in vec3 clr;

out vec3 vertClr;

uniform float uTime;

void main(){
    gl_Position = vec4(pos, 1.0);
    vertClr = clr;
}
