#version 460 core

in vec2 vTexCoords;
in vec3 vVertPos;

out vec4 oFragColor;

void discardForCircle(float min, float max);

void main()
{
	discardForCircle(0.4f, 1.f);

	oFragColor = vec4(0.047f, 0.690f, 0.357f, 1.0f);
}

void discardForCircle(float min, float max)
{
	float d = vVertPos.x * vVertPos.x + vVertPos.y * vVertPos.y;
	if (d > pow(max, 2) || d < pow(min, 2))
		discard;
}

//in VS_OUT gsOUT;
//
//out vec4 oFragColor;
//
//uniform sampler2D baseColor;
//uniform sampler2D metallicRoughness;
//uniform sampler2D normal;
//
//void main()
//{
//	vec3 color = vec3(texture(baseColor, vec2(gsOUT.texcoord)));// +vec3(gsOUT.color);
//	vec3 norm = vec3(texture(normal, vec2(gsOUT.texcoord)));
//
//	vec3 simple_light = -dot(normalize(gsOUT.position), normalize(norm)) * color;
//
//	oFragColor = vec4(color + simple_light, 1.0f);
//}