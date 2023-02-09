#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(a_Position, 1.0f);
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 330 core

out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;			

void main()
{
				
	color = texture(u_Texture, v_TexCoord) * u_Color;
}
