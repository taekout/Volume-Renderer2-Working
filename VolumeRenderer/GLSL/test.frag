#version 330

uniform sampler2D volumeLUT;

in vec2 UV;

layout(location=0) out vec4 outColor;

void main()
{
    //outColor = vec4(1.0, 0.0, 0.0, 1.0);
	outColor = texture2D(volumeLUT, UV.xy);
}