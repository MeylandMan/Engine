#pragma once

#include <math/math_main.h>

#define MAX_BONE_INFLUENCE 4
struct Vertex {
	vec3 Position;
	vec2 TexCoord;
	vec3 Normal;
	vec3 Tangent;
	vec3 Bitangent;
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct ShortVertex {
	vec3 Position;
	vec3 Normal;
};

struct ShortTVertex {
	vec3 Position;
	vec2 TexCoord;
	vec3 Normal;
};

struct ShortCVertex {
	vec3 Position;
	vec4 Color;
	vec3 Normal;
};