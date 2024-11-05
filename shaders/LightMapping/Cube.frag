#version 410 core
out vec4 fragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec4 color;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;
in vec3 v_Normal;
in vec2 v_TexCoords;

uniform vec3 u_ViewPosition;

uniform Material material;
uniform Light light;

void main()
{
	vec3 lightColor = light.color.xyz;

	// Ambiant
	vec3 ambiant =  light.ambient * texture(material.diffuse, v_TexCoords).rgb;
	
	// Diffuse
	vec3 lightDir = normalize(light.position - FragPos);
	float NdotL = max(dot(normalize(v_Normal), lightDir), 0.0);
	vec3 diffuse = light.diffuse * NdotL *  texture(material.diffuse, v_TexCoords).rgb;

	// Specular
	vec3 viewDir = normalize(u_ViewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, normalize(v_Normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = lightColor * light.specular * texture(material.specular, v_TexCoords).rgb * spec;

	fragColor = vec4(ambiant + diffuse + specular, 1.0);
}