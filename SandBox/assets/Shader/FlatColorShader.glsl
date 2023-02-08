#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(a_Position, 1.0f);
}


#type fragment
#version 330 core
			
out vec4 color;

uniform vec3 u_Color;

void main()
{
				
	color = vec4(u_Color, 1.0f);
}