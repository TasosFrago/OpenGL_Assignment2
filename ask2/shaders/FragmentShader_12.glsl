#version 330 core
uniform vec3 overideColor;

out vec4 FragColor;

void main()
{
		FragColor = vec4(overideColor, 1.0f);
}
