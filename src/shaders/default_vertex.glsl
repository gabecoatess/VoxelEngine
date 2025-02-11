#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 data;
uniform vec3 topOffset;

out vec3 datas;

void main()
{
	datas = data;
	gl_Position = vec4(aPos.x + topOffset.x, aPos.y + topOffset.x * 0.5, aPos.z + topOffset.x, 1.0);
}