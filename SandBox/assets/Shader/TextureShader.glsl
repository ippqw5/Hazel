#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;
out vec2 v_ScreenPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(a_Position, 1.0f);
	v_TexCoord = a_TexCoord;
	v_ScreenPos = gl_Position.xy;
}

#type fragment
#version 330 core

out vec4 color;

in vec2 v_TexCoord;
in vec2 v_ScreenPos;

uniform vec4 u_Color;
uniform float u_TilingFactor;
uniform float u_Dim;
uniform sampler2D u_Texture;			

void main()
{
	float dist = 1.0f - distance(v_ScreenPos * u_Dim, vec2(0.0f));
	dist = clamp(dist, 0.0f, 1.0f);
	color = texture(u_Texture, v_TexCoord * u_TilingFactor) * u_Color * dist;
}
