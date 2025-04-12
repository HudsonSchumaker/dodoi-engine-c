#version 410

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

// uniform float angle;

uniform mat4 model;			// model matrix
uniform mat4 view;			// view matrix
uniform mat4 projection;	// projection matrix

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main() {
   //vec2 point2d = aPoints.xy;
   //mat2 rotate = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
   //gl_Position = vec4(0.60 * rotate * point2d, 0.0, 1.0);
   //color = aColor;

    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoord = aTexCoord;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
 }
