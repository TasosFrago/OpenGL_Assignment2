#version 330 core
in vec3 color;
uniform vec3 overideColor;

out vec4 FragColor;

void main()
{
	if(overideColor != vec3(0.0)) {
		FragColor = vec4(overideColor, 1.0f);
	} else {
		FragColor = vec4(color, 1.0f);
	}
}
