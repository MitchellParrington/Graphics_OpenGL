#version 460 core

layout(location = 0) in vec3 iVertPos;
layout(location = 1) in vec2 iTexCoords;

out vec2 vTexCoords;
out vec3 vVertPos;

void main()
{
	vTexCoords = iTexCoords;
	vVertPos = iVertPos;
	gl_Position = vec4(iVertPos, 1.0f);
}