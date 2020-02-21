#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform float ElapsedTime;
uniform int Option;
 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	vec2 new_texcoord;

	if (Option == 1) {
		new_texcoord = vec2(texcoord.x + (ElapsedTime / 10), texcoord.y);
	} else {
		new_texcoord = texcoord;
	}

	vec4 color1 = texture2D(texture_1, new_texcoord);

	if (color1.a < 0.5f) {
		discard;
	}

	vec4 color2 = texture2D(texture_2, new_texcoord);

	if (color2.a < 0.5f) {
		discard;
	}

	out_color = mix(color1, color2, 0.5f);
}