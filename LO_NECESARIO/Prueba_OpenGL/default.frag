#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
uniform vec4 lightColor1;
// Gets the position of the light from the main function
uniform vec3 lightPos;
uniform vec3 lightPos1;
// Gets the position of the camera from the main function
uniform vec3 camPos;

void main()
{
    // ambient lighting
    float ambient = 0.30f;

    // Common variables
    vec3 normal = normalize(Normal);
    vec3 viewDirection = normalize(camPos - crntPos);

    // diffuse and specular lighting for the first light
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
    float specular = specAmount * 1.0f; // specularLight is 1.0f

    // diffuse and specular lighting for the second light
    vec3 lightDirection1 = normalize(lightPos1 - crntPos);
    float diffuse1 = max(dot(normal, lightDirection1), 0.0f);
    vec3 reflectionDirection1 = reflect(-lightDirection1, normal);
    float specAmount1 = pow(max(dot(viewDirection, reflectionDirection1), 0.0f), 8);
    float specular1 = specAmount1 * 1.0f; // specularLight is 1.0f

    // Combining the results
    vec4 lightEffect1 = lightColor * (diffuse + ambient + specular);
    vec4 lightEffect2 = lightColor1 * (diffuse1 + ambient + specular1);

    // outputs final color
    FragColor = texture(tex0, texCoord) * (lightEffect1 + lightEffect2);
}
