#version 410
in vec2 uv;
uniform sampler2D myTexture;
out vec4 fragColor;

void main() {
    fragColor = texture(myTexture, uv);
}
