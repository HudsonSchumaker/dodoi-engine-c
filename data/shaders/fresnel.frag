#version 410 core

in vec3 FragPos;  // Fragment position in world space
in vec3 Normal;   // Interpolated normal
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 eye;           // Camera position
uniform sampler2D texture0; // Card base texture
uniform vec3 lightPos;      // Light source position
uniform vec3 lightColor;    // Light color

void main() {
    // Base color from texture
    vec3 albedo = texture(texture0, TexCoords).rgb;

    // Compute normal
    vec3 normal = normalize(Normal);
    
    // Light direction
    vec3 lightDir = normalize(lightPos - FragPos);
    
    // View direction
    vec3 viewDir = normalize(eye - FragPos);
    
    // Reflect light (specular)
    vec3 reflectDir = reflect(-lightDir, normal);
    
    // Specular intensity (Blinn-Phong)
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128.0);
    
    // Fresnel effect (stronger reflections at edges)
    float fresnel = pow(1.0 - max(dot(normal, viewDir), 0.0), 3.0);
    
    // Final metallic color
    vec3 metalColor = mix(albedo, lightColor * spec * fresnel, 0.6);
    
    FragColor = vec4(metalColor, 1.0);
}
