#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;

uniform mat4 sModelMatrix;
uniform mat4 sViewMatrix;
uniform mat4 sProjectionMatrix;

out vec3 color;
out vec2 texCoord;

void main()
{
	// Multiply matrices in reverse (p, v, m)
	gl_Position = sProjectionMatrix * sViewMatrix * sModelMatrix * vec4(aPos, 1.0);
	color = aColor;
	texCoord = aTexCoord;
}