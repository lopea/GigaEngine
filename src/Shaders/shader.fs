#version 330 core

in vec3 myPosition;
out vec4 FragColor;

void main()
{
    FragColor =  vec4(myPosition, 1.0f);
}
