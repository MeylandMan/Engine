#version 410 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 direction;
	vec4 color;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
};


out vec4 fragColor;

uniform vec3 u_ViewPosition;

uniform Material material;
uniform Light light;

in vec3 FragPos;
in vec3 v_Normal;

in vec2 v_TexCoords;

uniform int u_LightChoice;

void main()
{
	vec3 lightColor = light.color.xyz;

	// Ambiant
	vec3 ambiant =  light.ambient * texture(material.diffuse, v_TexCoords).rgb;

	// Diffuse
	vec3 lightDir = vec3(1.);

	if(u_LightChoice == 0)
		lightDir = normalize(-light.direction);
	else if(u_LightChoice == 1)
		lightDir = normalize(light.position - FragPos);

	float NdotL = max(dot(normalize(v_Normal), lightDir), 0.0);
	vec3 diffuse = light.diffuse * NdotL *  texture(material.diffuse, v_TexCoords).rgb;

	float distance = length(light.position - FragPos);
	float att = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));


	// Specular
	vec3 viewDir = normalize(u_ViewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, normalize(v_Normal));

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = lightColor * light.specular * texture(material.specular, v_TexCoords).rgb * spec;
	if(u_LightChoice != 0) {
		ambiant *= att;
		diffuse *= att;
		specular *= att;
	}
	fragColor = vec4(ambiant + diffuse + specular, 1.0);
	float theta = dot(lightDir, normalize(-light.direction));

	if(theta < light.cutOff && u_LightChoice == 2)
	{
		fragColor = vec4(ambiant, 1.0);
	}

	
}