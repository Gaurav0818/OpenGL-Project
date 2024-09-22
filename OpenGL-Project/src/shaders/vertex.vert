#version 460

layout (location=0) in vec3 pos;

out vec3 vCol;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	vec4 value = projection * model * vec4(pos.x, pos.y , pos.z, 1.0);
	gl_Position = value;
	vCol = vec3(clamp ( pos, 0.0, 1.0));
}
