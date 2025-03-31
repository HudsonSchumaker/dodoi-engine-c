#version 410

in vec2 textCoords;
uniform sampler2D texture0;
out vec4 fragColor;

void main() {
    fragColor = texture(texture0, textCoords);
}
