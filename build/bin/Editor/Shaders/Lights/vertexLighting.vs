
#version 460 core
layout (location = 0) in vec3 aPos;

//out vec4 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    //vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}