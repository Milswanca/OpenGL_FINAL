#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 aColour;
layout (location = 3) in vec3 aUV;

uniform mat4 View;
uniform mat4 Projection;
uniform mat4 Model;

out vec3 FragPos;
out vec3 Normal;
out vec3 UV;
out vec4 Colour;

void main()
{
    gl_Position = Projection * View * Model * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor

	FragPos = vec3(Model * vec4(aPos, 1.0f));
	Normal = aNormal;
	UV = aUV;
	Colour = aColour;
}