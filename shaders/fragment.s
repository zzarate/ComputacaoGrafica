#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{

    // ambient
    vec3 ambient = 0.3 * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);
}
