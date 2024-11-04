#version 410 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
vec3 position;
vec3 ambient;
vec3 diffuse;
vec3 specular;
};

out vec4 fragColor;

uniform vec3 u_LightPosition;
uniform vec4 u_LightColor;

uniform vec3 u_ViewPosition;

uniform Material material;
uniform Light light;

in vec3 FragPos;
in vec3 v_Normal;

in vec2 v_TexCoords;

void main()
{
	vec3 lightColor = u_LightColor.xyz;

	// Ambiant
	vec3 ambiant =  light.ambient * vec3(texture(material.diffuse, v_TexCoords));

	// Diffuse
	vec3 lightDir = normalize(u_LightPosition - FragPos);
	float NdotL = max(dot(normalize(v_Normal), lightDir), 0.0);
	vec3 diffuse = light.diffuse * (NdotL *  vec3(texture(material.diffuse, v_TexCoords)));

	// Specular
	vec3 viewDir = normalize(u_ViewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, normalize(v_Normal));

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = lightColor * light.specular * (vec3(texture(material.specular, v_TexCoords)) * spec) ;

	fragColor = vec4(ambiant + diffuse + specular, 1.0);
}