$input v_texcoord0

#include <bgfx_shader.sh>

SAMPLER2D(s_input, 0);

void main()
{
	gl_FragColor = vec4(texture2D(s_input, v_texcoord0).rgb, 1.0);
}