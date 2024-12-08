#version 460 core

layout(location = 0) in vec2 vertexData;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * model * vec4(vertexData, 0.0f, 1.0f);
}