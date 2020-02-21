#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform sampler2D texture;

// Output values to fragment shader
out vec3 world_position;
out vec3 world_normal;
out vec3 v_pos;
out vec2 texcoord;

void main()
{
	// TODO : pass v_texture_coord as output to Fragment Shader
	texcoord = v_texture_coord;
	float height = texture2D(texture, texcoord).r;
	vec3 new_pos = vec3(v_position.x, 5 * height, v_position.z);
	vec2 texelSize = vec2(1.0/256.0, 1.0/256.0);

	float heightRight = texture2D(texture, vec2(texcoord.x + texelSize.x, texcoord.y)).r;
	float heightUp = texture2D(texture, vec2(texcoord.x, texcoord.y + texelSize.y)).r;

	float Hx = height - heightRight;
	float Hz = height - heightUp;

	vec3 normal = normalize(vec3(5 * Hx, 1, 5 * Hz));

	world_position = (Model * vec4(v_position, 1)).xyz;
	world_normal = normalize(mat3(Model) * normal);
	v_pos = v_position;

	gl_Position = Projection * View * Model * vec4(new_pos, 1.0);
}
