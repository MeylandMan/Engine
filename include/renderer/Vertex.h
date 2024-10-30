#pragma once

#include <math/math_main.h>

struct Vertex {
	vec3 Position;
	vec4 Color;
	vec2 TexCoord;
	vec3 Normal;
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