#version 330

// TODO: get values from fragment shader
in vec3 frag_normal;
in vec3 culoare;
in vec3 normala;
in float time;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO: write pixel out color
	out_color = vec4(normala, 1) * cos(time);
}