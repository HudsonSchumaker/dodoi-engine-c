#version 410 core

layout (location = 0) in vec3 aPosition;			
layout (location = 1) in vec3 aNormal;	
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;		 // model matrix
uniform mat4 view;		 // view matrix
uniform mat4 projection; // projection matrix

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main() {
	TexCoord = aTexCoord;
    FragPos  = vec3(model * vec4(aPosition, 1.0));	     // vertex position in world space
    Normal   = mat3(transpose(inverse(model))) * aNormal; // normal direction in world space

	gl_Position = projection * view *  model * vec4(aPosition, 1.0);
}
