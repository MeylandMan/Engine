#version 410 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 in_TexCoord;
//layout (location = 2) in vec3 in_Normal;

out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
	mat4 MATRIX_VIEW_PROJECTION = u_Model * u_View * u_Proj;

	gl_Position = vec4(in_Position, 1) * MATRIX_VIEW_PROJECTION;
	v_TexCoord = in_TexCoord;
}