#version 410 core

out vec4 fragColor;
uniform vec4 u_ObjectColor;
uniform vec4 u_LightColor;
uniform int u_IsLight;

void main()
{
	float ambiantStrength = 0.1;
	if(u_IsLight == 1)
		ambiantStrength = 1;
	vec4 ambiant = u_LightColor * ambiantStrength;

	fragColor = ambiant * u_ObjectColor;
}