#version 330 core
out vec4 fragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight dirLight;

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct SpotLight {
    vec3 position;  
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

#define NR_SPOT_LIGHTS 1
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

in vec3 FragPos;
in vec3 v_Normal;
in vec2 v_TexCoords;

uniform vec3 u_ViewPosition;

uniform Material material;
uniform Light light;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	fragColor = vec4(ambiant + diffuse + specular, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {

	vec3 lightDir = normalize(-light.direction);

	// diffuse
	float NDotL = max(dot(normal, lightDir), 0.0);

	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// combine
	vec3 ambient = light.ambient * texture(material.diffuse, v_TexCoords).rgb;
	vec3 diffuse = light.diffuse * NDotL * texture(material.diffuse, v_TexCoords).rgb;
	vec3 specular = light.specular * spec * texture(material.specular, v_TexCoords).rgb;
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

	vec3 lightDir = normalize(light.position - fragPos);

	// diffuse
	float NDotL = max(dot(normal, lightDir), 0.0);

	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// attenuation
	float distance = length(light.position - fragPos);
	float att = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// combine
	vec3 ambient = light.ambient * texture(material.diffuse, v_TexCoords).rgb;
	vec3 diffuse = light.diffuse * NDotL * texture(material.diffuse, v_TexCoords).rgb;
	vec3 specular = light.specular * spec * texture(material.specular, v_TexCoords).rgb;

	ambient *= att;
	diffuse *= att;
	specular *= att;
	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	
	vec3 lightDir = normalize(light.position - fragPos);

	// Diffuse
	float NdotL = max(dot(normalize(normal), lightDir), 0.0);

	// Specular
	vec3 reflectDir = reflect(-lightDir, normalize(normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// CutOff (Smoother)
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	// Attenuation
	float distance = length(light.position - fragPos);
	float att = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// combine
	vec3 ambient =  light.ambient * texture(material.diffuse, v_TexCoords).rgb;
	vec3 diffuse = light.diffuse * NdotL *  texture(material.diffuse, v_TexCoords).rgb;
	vec3 specular = lightColor * light.specular * texture(material.specular, v_TexCoords).rgb * spec;

	ambient *= att;
	diffuse *= att;
	specular *= att;

	diffuse *= intensity;
	specular *= intensity;
	return (ambient + diffuse + specular);
}
