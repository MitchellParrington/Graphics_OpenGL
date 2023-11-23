#version 460 core

in struct {
	vec4 glposition;
	vec4 color;
	vec3 position;
	vec3 normal;
	vec3 texcoord;
} VSO;

out vec4 oFragColor;

void main()
{
	//vec3 color = vec3(texture(baseColor, vec2(VSO.texcoord)));// +vec3(VSO.color);
	//vec3 norm = vec3(texture(normal, vec2(VSO.texcoord)));
	//
	//vec3 simple_light = -dot(normalize(VSO.position), normalize(norm)) * color;
	//
	//oFragColor = vec4(color + simple_light, 1.0f);

	//oFragColor = vec4(normalize(color + vec3(VSO.color)), 1.0f);

	//oFragColor = vec4(1.5f, 0.0f, 0.2f, 1.0f);

	//oFragColor = VSO.color;
	//oFragColor = vec4(vec3(texture(baseColor, vec2(VSO.texcoord))), 1.0f);
	//oFragColor = vec4(-dot(normalize(VSO.position), normalize(VSO.normal)) * vec3(oFragColor), 1.0f);
	oFragColor = vec4(1, 1, 1, 1);
}