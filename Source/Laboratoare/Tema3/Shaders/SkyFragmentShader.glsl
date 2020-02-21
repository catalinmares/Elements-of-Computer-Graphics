#version 330
 
uniform sampler2D texture;
 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	vec2 new_texcoord = texcoord;

	out_color = texture2D(texture, new_texcoord);
}