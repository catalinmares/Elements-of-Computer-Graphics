#version 330

// TODO: get vertex attributes from each location
layout(location=0) in vec3 my_coord;
layout(location=3) in vec3 my_color;
layout(location=2) in vec3 my_normal;
layout(location=1) in vec2 my_TextCoord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float ElapsedTime;

// TODO: output values to fragment shader
out vec3 culoare;
out vec3 normala;
out float time;

void main()
{
	// TODO: send output to fragment shader
	culoare = my_color;
	normala = my_normal;
	time = ElapsedTime;

	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * vec4(my_coord * cos(ElapsedTime), 1.0);
}
