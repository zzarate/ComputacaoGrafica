// vertex shader
#version 330 core
layout (location = 0) in vec3 aPos;  // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord; // the texture coordinate variable has attribute position 1
layout (location = 2) in vec3 aNormal; // the normal variable has attribute position 2

out vec3 FragPos; // output to the fragment shader
out vec3 Normal;  // output to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0)); // calculate the vertex position in world coordinates
    Normal = mat3(transpose(inverse(model))) * aNormal; // transform the normal vector with the model matrix

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
