#version 400
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform vec3 offset;

void main()
{
    gl_Position = vec4(aPos + offset, 1.0);
    ourColor = gl_Position.xyz;
}