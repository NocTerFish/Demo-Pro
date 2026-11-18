#version 460 core

in vec4 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

// ── 纹理采样器 ──
uniform sampler2D tex1;
uniform sampler2D tex2;

uniform float mixRate;

void main()
{
	// texture(sampler, uv) = 在 uv 处采样
	vec4 c1 = texture(tex1, TexCoord);
	vec4 c2 = texture(tex2, TexCoord);

	FragColor = mix(c1, c2, mixRate);
}