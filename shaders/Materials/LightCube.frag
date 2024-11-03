#version 410 core
out vec4 fragColor;
uniform vec4 u_LightColor;

void main()
{
	fragColor = u_LightColor;
}