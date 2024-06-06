#version 330 core

out vec4 FragColor;

uniform vec4 lightColor;
uniform vec4 lightColor1;

void main()
{
    // Combinar los colores de las dos luces
    FragColor = lightColor + lightColor1;
}
