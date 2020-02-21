#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;
in vec3 v_pos;
in vec2 texcoord;

// Uniforms for light properties
uniform vec3 light1_direction;
uniform vec3 light1_position;
uniform vec3 light2_direction;
uniform vec3 light2_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform sampler2D texture;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	vec2 new_texcoord = texcoord;

	vec4 object_color = texture2D(texture, new_texcoord);

	vec3 normal = normalize(world_normal);
	vec3 V = normalize(eye_position - world_position);
	float cut_off = radians(60.0);
	float spot_light_limit = cos(cut_off);

	// define ambient light component
	float ambient_light = 0.25 * material_kd;

	// Spotlight 1
	vec3 L1 = normalize(light1_position - world_position);
	vec3 H1 = normalize(L1 + V);

	// TODO: compute diffuse light component
	float diffuse_light1 = material_kd * max (dot(normal, L1), 0);

	// TODO: compute specular light component
	float specular_light1 = 0;

	if (diffuse_light1 > 0) {
		specular_light1 = material_ks * pow(max(dot(normal, H1), 0), material_shininess);
	}

	// Spotlight 2
	vec3 L2 = normalize(light2_position - world_position);
	vec3 H2 = normalize(L2 + V);

	// TODO: compute diffuse light component
	float diffuse_light2 = material_kd * max (dot(normal, L2), 0);

	// TODO: compute specular light component
	float specular_light2 = 0;

	if (diffuse_light2 > 0) {
		specular_light2 = material_ks * pow(max(dot(normal, H2), 0), material_shininess);
	}

	float spot_light1 = dot(-L1, light1_direction);

	float linear_att1 = (spot_light1 - spot_light_limit) / (1 - spot_light_limit);
	float light_att_factor1 = pow(linear_att1, 2);
	
	float light1 = ambient_light + light_att_factor1 * (diffuse_light1 + specular_light1);

	float spot_light2 = dot(-L2, light2_direction);

	float linear_att2 = (spot_light2 - spot_light_limit) / (1 - spot_light_limit);
	float light_att_factor2 = pow(linear_att2, 2);
	
	float light2 = ambient_light + light_att_factor2 * (diffuse_light2 + specular_light2);
	
	if (spot_light1 > cos(cut_off)) {
		out_color = vec4(object_color * vec4(light1));
	} else if (spot_light2 > cos(cut_off)) {
		out_color = vec4(object_color * vec4(light2));
	} else {
		out_color = vec4(object_color * 0.25);
	}
}