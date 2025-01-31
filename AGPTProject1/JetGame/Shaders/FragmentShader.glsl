#version 330 core

in vec3 Color;
in vec2 TexCoord;

out vec4 outColor;

uniform sampler2D ourTexture;

void main()
{
    outColor = texture(ourTexture, TexCoord);

    if (outColor == vec4(1.0f, 0.0f, 1.0f, 1.0f))
        discard;
}
