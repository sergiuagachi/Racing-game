#version 330

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec3 vertex_coordinate;
layout(location = 3) in vec3 vertex_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;
uniform int Type;

// TODO: output values to fragment shader
out vec3 frag_vertex_position;
out vec3 frag_vertex_normal;
out vec3 frag_vertex_coordinate;
out vec3 frag_vertex_color;

void main()
{
	// TODO: send output to fragment shader
	frag_vertex_position = vertex_position;
	frag_vertex_normal = vertex_normal;
	frag_vertex_coordinate = vertex_coordinate;
	if(Type == 0){
		float help = (abs(cos(Time * 0.1)) + 0.3f);
		if(help <= 0.9)
			frag_vertex_color = vertex_color * (abs(cos(Time * 0.1)) + 0.3f);
		else
			frag_vertex_color = vertex_color * 0.9;
	}
	else{
		float help = (abs(cos(Time * 0.1)));
		if(help >= 0.2)
			frag_vertex_color = vertex_color * abs(cos(Time * 0.1));
		else
			frag_vertex_color = vertex_color * 0.2;
	}

	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * vec4(vertex_position, 1.0);
}