#version 330

// TODO: get values from fragment shader
in vec3 frag_vertex_position;
in vec3 frag_vertex_normal;
in vec3 frag_vertex_coordinate;
in vec3 frag_vertex_color;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO: write pixel out color
	out_color = vec4(frag_vertex_color, 1);
}