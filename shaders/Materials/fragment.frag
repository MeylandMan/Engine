#version 410 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
vec3 position;
vec3 ambient;
vec3 diffuse;
vec3 specular;
};

out vec4 fragColor;
uniform vec4 u_ObjectColor;

uniform vec3 u_LightPosition;
uniform vec4 u_LightColor;

uniform vec3 u_ViewPosition;

uniform Material material;
uniform Light light;

in vec3 FragPos;
in vec3 v_Normal;

void main()
{
	vec3 lightColor = vec3(u_LightColor.x, u_LightColor.y, u_LightColor.z);
	vec3 ObjectColor = vec3(u_ObjectColor.x, u_ObjectColor.y, u_ObjectColor.z);

	// Ambiant
	vec3 ambiant = vec3(1.) * material.ambient;

	// Diffuse
	vec3 lightDir = normalize(u_LightPosition - FragPos);
	float NdotL = max(dot(normalize(v_Normal), lightDir), 0.0);
	vec3 diffuse = vec3(1.) * (NdotL * material.diffuse);

	// Specular
	vec3 viewDir = normalize(u_ViewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, normalize(v_Normal));

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = vec3(1.) * (material.specular * spec) ;

	fragColor = vec4((ambiant + diffuse + specular) * ObjectColor, 1.0);
}