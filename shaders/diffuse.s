#version 330 core
out vec4 FragColor;

in vec3 FragPos;  // input from the vertex shader
in vec3 Normal;   // input from the vertex shader

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;  // position of the light source
uniform vec3 viewPos;   // position of the camera

void main()
{

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // combine results
    vec3 result = diffuse * objectColor;
    FragColor = vec4(result, 1.0);
}
