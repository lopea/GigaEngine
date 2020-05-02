#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float xOffset;

out vec3 myColor; // output a color to the fragment shader

void main()
{
    gl_Position = vec4(xOffset + aPos.x, -aPos.y, aPos.z, 1.0f);
    myColor = aColor; // set myColor to the input color we got from the vertex data
}