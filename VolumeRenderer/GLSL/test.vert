#version 330

layout(location=0) in vec4 inPosition;

layout(location=1) in vec2 gUV;

uniform mat4 projection;
uniform mat4 modelview;

out vec2 UV;

void main()
{
	UV = gUV;

	gl_Position = projection * modelview * inPosition;
}