#version 410

layout(location = 0) in vec3 aPoints;
layout(location = 1) in vec2 aTextCoords;

// uniform float angle;

uniform mat4 model;			// model matrix
uniform mat4 view;			// view matrix
uniform mat4 projection;	// projection matrix

out vec2 textCoords;

void main() {
   //vec2 point2d = aPoints.xy;
   //mat2 rotate = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
   //gl_Position = vec4(0.60 * rotate * point2d, 0.0, 1.0);
   //color = aColor;

   textCoords = aTextCoords;
   gl_Position = projection * view * model * vec4(aPoints, 1.0f);
 }