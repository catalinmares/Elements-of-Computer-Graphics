#version 330

// TODO: get vertex attributes from each location
layout(location=0) in vec3 my_coord;
layout(location=1) in vec3 my_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float ElapsedTime;
uniform vec3 object_color;

// TODO: output values to fragment shader
out vec3 culoare;

void main()
{
	culoare = object_color;

	gl_Position = Projection * View * Model * vec4(my_coord, 1);
}
