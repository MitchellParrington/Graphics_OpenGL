#version 460 core

layout(location = 0) in vec3 aVertPosition;
layout(location = 1) in vec3 aVertNormal;
layout(location = 2) in vec3 aTexCoord;
layout(location = 3) in vec3 aVertTangent;
layout(location = 4) in vec3 aVertBitangent;
layout(location = 5) in vec4 aVertColor;


out struct {
	vec4 glposition;
	vec4 color;
	vec3 position;
	vec3 normal;
	vec3 texcoord;
} VSO;

uniform mat4 uMvp;
uniform mat4 uMv;
uniform mat3 uMvNorm;

void main()
{
	VSO.color = aVertColor;
	VSO.position = vec3(uMv * vec4(aVertPosition, 1.0f));
	VSO.normal = uMvNorm * aVertNormal;
	VSO.texcoord = aTexCoord;
	VSO.glposition = uMvp * vec4(aVertPosition, 1.0f);
	gl_Position = VSO.glposition;
}