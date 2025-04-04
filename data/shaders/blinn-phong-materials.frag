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

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Light light;
uniform Material material;

void main() {
	// Ambient -------------------------------------------------------------------------
	vec3 ambient = light.ambient * material.ambient;

	// Diffuse -------------------------------------------------------------------------
	vec3 normal   = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff    = max(dot(normal, lightDir), 0.0);
	vec3 diffuse  = light.diffuse * (diff * material.diffuse);

	// Specular - Blinn-Phong ----------------------------------------------------------
	vec3 viewDir  = normalize(viewPos - FragPos);
	vec3 halfDir  = normalize(lightDir + viewDir);
	float NDotH   = max(dot(normal, halfDir), 0.0);
	vec3 specular = light.specular * material.specular * pow(NDotH, material.shininess);

	// result
	vec3 result = ambient + diffuse + specular;
	FragColor   = vec4(result, 1.0);
}
