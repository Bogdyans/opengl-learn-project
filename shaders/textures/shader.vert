#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform vec2 offset;

uniform float scale;

void main()
{
    gl_Position = vec4((aPos.xy + offset.xy)*scale, aPos.z, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}