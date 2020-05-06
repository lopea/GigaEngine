#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform mat4 MVP;
out vec3 myPosition; // output a color to the fragment shader

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0f);
    myPosition = aPos; // set myColor to the input color we got from the vertex data
}
