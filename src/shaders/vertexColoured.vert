#version 330 core

layout (location=0) in vec3 pos;
layout (location=1) in vec3 clr;

out vec3 vertClr;

uniform float uTime;
uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main(){
    gl_Position = uProjection * uView * uModel * vec4(pos, 1.0);
    vertClr = clr;
}
