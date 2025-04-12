#version 410

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture0;

void main() {
    vec3 color = texture(texture0, TexCoord).rgb;
    FragColor = vec4(color, 1.0);
}