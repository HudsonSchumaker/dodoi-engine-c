#version 410 core

struct Material {
    vec3 ambient;
    vec3 specular;
    float shininess;
};

struct Light {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
  
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform Light light;
uniform Material material;
uniform vec3 eye;
uniform sampler2D texture0;
uniform sampler2D texture1;

out vec4 frag_color;

void main() { 
    vec3 albedo = gl_FrontFacing ? texture(texture0, TexCoord).rgb 
                                 : texture(texture1, TexCoord).rgb;

    // Normal handling
    vec3 normal = normalize(Normal);
    if (!gl_FrontFacing) {
        normal = -normal; // Flip normal for the back face
    }
    // Light calculations
    vec3 lightDir = normalize(-light.direction);
    float NdotL = max(dot(normal, lightDir), 0.0);

    // Ambient -------------------------------------------------------------------------
    vec3 ambient = light.ambient * material.ambient * albedo;
  	
    // Diffuse -------------------------------------------------------------------------
    vec3 diffuse  = light.diffuse * NdotL * albedo;
    
    // Specular - Blinn-Phong ----------------------------------------------------------
	vec3 viewDir  = normalize(eye - FragPos);
	vec3 halfDir  = normalize(lightDir + viewDir);
	float NDotH   = max(dot(normal, halfDir), 0.0);
	vec3 specular = light.specular * material.specular * pow(NDotH, material.shininess);
		
    frag_color = vec4(ambient + diffuse + specular, 1.0);
}
