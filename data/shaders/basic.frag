#version 410

//in vec3 color;
in vec2 textCoords;

uniform sampler2D myTexture;

out vec4 fragColor;

void main() {
    fragColor = texture(myTexture, textCoords);
}
