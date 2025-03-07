#version 400 core
layout (location = 0) in vec3 aPos;

uniform vec3 offset;

void main()
{
    gl_Position = vec4(
        aPos.x,
        -aPos.y,
        aPos.z,
        1.0);
}