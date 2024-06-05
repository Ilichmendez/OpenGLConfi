#include "default.frag.h"

const char* Fragment::getFrag(std::string ambient) {
    std::stringstream fragmentShader;
    fragmentShader 
        << "#version 330 core\n"
        << "out vec4 FragColor;\n"
        << "in vec3 color;\n"
        << "in vec2 texCoord;\n"
        << "in vec3 Normal;\n"
        << "in vec3 crntPos;\n"
        << "\n"
        << "uniform sampler2D tex0;\n"
        << "uniform vec4 lightColor;\n"
        << "uniform vec3 lightPos;\n"
        << "uniform vec3 camPos;\n"
        << "void main()\n"
        << "{\n"
        << "    float ambient = " << ambient << "f;\n"
        << "    vec3 normal = normalize(Normal);\n"
        << "    vec3 lightDirection = normalize(lightPos - crntPos);\n"
        << "    float diffuse = max(dot(normal, lightDirection), 0.0f);\n"
        << "    float specularLight = 1.0f;\n"
        << "    vec3 viewDirection = normalize(camPos - crntPos);\n"
        << "    vec3 reflectionDirection = reflect(-lightDirection, normal);\n"
        << "    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);\n"
        << "    float specular = specAmount * specularLight;\n"
        << "    FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);\n"
        << "}\n";

    // Convert the std::string to const char*
    static std::string shaderStr = fragmentShader.str();

    // Open the file and write the shader code to it

    return shaderStr.c_str();
}