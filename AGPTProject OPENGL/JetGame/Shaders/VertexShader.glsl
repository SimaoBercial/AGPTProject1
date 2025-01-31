#version 330 core

in vec3 position;
in vec3 color;
in vec2 texCoord;

out vec3 Color;
out vec2 TexCoord;

uniform int frameIndex; 
uniform vec2 spriteSheetSize;

void main()
{
    Color = color;

    int cols = int(spriteSheetSize.x);
    int rows = int(spriteSheetSize.y);

    int column = frameIndex % cols;
    int row = frameIndex / cols;

    float texWidth = 1.0 / float(cols);
    float texHeight = 1.0 / float(rows);

    TexCoord = texCoord * vec2(texWidth, texHeight) + vec2(float(column) * texWidth, 1.0 - float(row + 1) * texHeight);

    gl_Position = vec4(position, 1.0);
}
