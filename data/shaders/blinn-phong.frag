//-----------------------------------------------------------------------------
// blinn-phong.frag by Hudson Schumaker
// Copyright (c) 2020-2025 SchumakerTeam. All Rights Reserved.
//
// Fragment shader for blinn-phong.
//-----------------------------------------------------------------------------
#version 410 core

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_map;
uniform vec3 lightPos;	 // for diffuse
uniform vec3 lightColor; // for diffuse
uniform vec3 viewPos;	 // for specular

out vec4 frag_color;

void main() {
    // Ambient ---------------------------------------------------------
    float ambientFactor = 0.1;
    vec3 ambient = lightColor * ambientFactor;
  	
    // Diffuse ------------------------------------
    vec3 normal   = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float NDotL   = max(dot(normal, lightDir), 0.0);
    vec3 diffuse  = lightColor * NDotL;
    
    // Specular (Blinn-Phong)-------------------------------------------
	float shininess = 32.0;
	float specularFactor = 0.8;
	
    vec3 viewDir  = normalize(viewPos - FragPos);
	vec3 halfDir  = normalize(lightDir + viewDir);
	float NDotH   = max(dot(normal, halfDir), 0.0);
	vec3 specular = lightColor * specularFactor * pow(NDotH, shininess);
	
	vec4 texel = texture(texture_map, TexCoord);
    frag_color = vec4(ambient + diffuse + specular, 1.0) * texel;
}
