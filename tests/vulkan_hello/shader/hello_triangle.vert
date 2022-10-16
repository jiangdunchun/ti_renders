#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 iPos;
layout(location = 1) in vec3 iColor;

layout(location = 0) out vec4 gColor;

void main() {
	gColor = vec4(iColor, 1.0);
    gl_Position = vec4(iPos, 1.0);
}