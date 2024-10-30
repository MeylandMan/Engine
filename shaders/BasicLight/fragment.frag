#version 410 core

out vec4 fragColor;
uniform vec4 u_ObjectColor;

uniform vec3 u_LightPosition;
uniform vec4 u_LightColor;
uniform int u_IsLight;

in vec3 FragPos;
in vec3 v_Normal;

void main()
{
	vec3 lightColor = vec3(u_LightColor.x, u_LightColor.y, u_LightColor.z);
	vec3 ObjectColor = vec3(u_ObjectColor.x, u_ObjectColor.y, u_ObjectColor.z);

	float ambiantStrength = 0.1;
	if(u_IsLight == 1)
		ambiantStrength = 1;
	vec3 ambiant = lightColor * ambiantStrength;

	vec3 lightDir = normalize(u_LightPosition - FragPos);

	float NdotL = max(dot(normalize(v_Normal), lightDir), 0.0);
	vec3 diffuse = lightColor * NdotL;

	fragColor = vec4((ambiant + diffuse) * ObjectColor, 1.0);
}