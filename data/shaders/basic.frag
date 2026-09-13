//-----------------------------------------------------------------------------
// basic.frag by Hudson Schumaker
// Copyright (c) 2020-2025 SchumakerTeam. All Rights Reserved.
//
// Fragment shader for basic rendering.
//-----------------------------------------------------------------------------
#version 410
in vec2 uv;
uniform sampler2D myTexture;
out vec4 fragColor;

void main() {
    fragColor = texture(myTexture, uv);
}
