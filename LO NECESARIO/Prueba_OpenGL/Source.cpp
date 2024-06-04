#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"



const unsigned int width = 800;
const unsigned int height = 800;



// Vertices coordinates with colors, texture coordinates, and normals
GLfloat vertices[] = {
	// Coordinates         // Colors           // TexCoords  // Normals
	-0.25f, -0.25f,  0.25f,  0.50f, 0.57f, 0.26f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,  // Front face
	 0.25f, -0.25f,  0.25f,  0.50f, 0.57f, 0.26f,  1.0f, 0.0f,  0.0f,  0.0f,  1.0f,  // Front face
	 0.25f,  0.25f,  0.25f,  0.50f, 0.57f, 0.26f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  // Front face
	-0.25f,  0.25f,  0.25f,  0.50f, 0.57f, 0.26f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,  // Front face

	-0.25f, -0.25f, -0.25f,  0.50f, 0.57f, 0.26f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,  // Back face
	 0.25f, -0.25f, -0.25f,  0.50f, 0.57f, 0.26f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,  // Back face
	 0.25f,  0.25f, -0.25f,  0.50f, 0.57f, 0.26f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,  // Back face
	-0.25f,  0.25f, -0.25f,  0.50f, 0.57f, 0.26f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,  // Back face

	-0.25f, -0.25f,  0.25f,  0.50f, 0.57f, 0.26f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,  // Left face
	-0.25f, -0.25f, -0.25f,  0.50f, 0.57f, 0.26f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,  // Left face
	-0.25f,  0.25f, -0.25f,  0.50f, 0.57f, 0.26f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,  // Left face
	-0.25f,  0.25f,  0.25f,  0.50f, 0.57f, 0.26f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,  // Left face

	 0.25f, -0.25f,  0.25f,  0.50f, 0.57f, 0.26f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,  // Right face
	 0.25f, -0.25f, -0.25f,  0.50f, 0.57f, 0.26f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,  // Right face
	 0.25f,  0.25f, -0.25f,  0.50f, 0.57f, 0.26f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  // Right face
	 0.25f,  0.25f,  0.25f,  0.50f, 0.57f, 0.26f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,  // Right face

	-0.25f, -0.25f,  0.25f,  0.50f, 0.57f, 0.26f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,  // Bottom face
	 0.25f, -0.25f,  0.25f,  0.50f, 0.57f, 0.26f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,  // Bottom face
	 0.25f, -0.25f, -0.25f,  0.50f, 0.57f, 0.26f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,  // Bottom face
	-0.25f, -0.25f, -0.25f,  0.50f, 0.57f, 0.26f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,  // Bottom face

	-0.25f,  0.25f,  0.25f,  0.50f, 0.57f, 0.26f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,  // Top face
	 0.25f,  0.25f,  0.25f,  0.50f, 0.57f, 0.26f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  // Top face
	 0.25f,  0.25f, -0.25f,  0.50f, 0.57f, 0.26f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,  // Top face
	-0.25f,  0.25f, -0.25f,  0.50f, 0.57f, 0.26f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f   // Top face
};

// Indices for vertices order
GLuint indices[] = {
	0, 1, 2, 2, 3, 0,   // Front face
	4, 5, 6, 6, 7, 4,   // Back face
	8, 9, 10, 10, 11, 8, // Left face
	12, 13, 14, 14, 15, 12, // Right face
	16, 17, 18, 18, 19, 16, // Bottom face
	20, 21, 22, 22, 23, 20  // Top face
};

// Light vertices
GLfloat lightVertices[] = {
	// Coordinates
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

// Light indices
GLuint lightIndices[] = {
	0, 1, 2, 0, 2, 3,   // Bottom face
	0, 4, 7, 0, 7, 3,   // Front face
	3, 7, 6, 3, 6, 2,   // Right face
	2, 6, 5, 2, 5, 1,   // Back face
	1, 5, 4, 1, 4, 0,   // Left face
	4, 5, 6, 4, 6, 7    // Top face
};

int main()
{
    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using 
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "Cubito"
    GLFWwindow* window = glfwCreateWindow(width, height, "Cubito", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, width, height);

    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("default.vert", "default.frag");
    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));
    // Links VBO attributes such as coordinates and colors to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Shader for light cube
    Shader lightShader("light.vert", "light.frag");
    // Generates Vertex Array Object and binds it
    VAO lightVAO;
    lightVAO.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    // Generates Element Buffer Object and links it to indices
    EBO lightEBO(lightIndices, sizeof(lightIndices));
    // Links VBO attributes such as coordinates and colors to VAO
    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    // Unbind all to prevent accidentally modifying them
    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    // Shader for second light cube
    Shader lightShader1("light.vert", "light.frag");
    // Generates Vertex Array Object and binds it
    VAO lightVAO1;
    lightVAO1.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO lightVBO1(lightVertices, sizeof(lightVertices));
    // Generates Element Buffer Object and links it to indices
    EBO lightEBO1(lightIndices, sizeof(lightIndices));
    // Links VBO attributes such as coordinates and colors to VAO
    lightVAO1.LinkAttrib(lightVBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    // Unbind all to prevent accidentally modifying them
    lightVAO1.Unbind();
    lightVBO1.Unbind();
    lightEBO1.Unbind();

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec4 lightColor1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos1 = glm::vec3(-0.5f, -0.5f, -0.5f);
    glm::mat4 lightModel1 = glm::mat4(1.0f);
    lightModel1 = glm::translate(lightModel1, lightPos1);

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    Texture brickTex("corazon.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    brickTex.texUnit(shaderProgram, "tex0", 0);

    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        shaderProgram.Activate();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
        glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor1"), lightColor1.x, lightColor1.y, lightColor1.z, lightColor1.w);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos1"), lightPos1.x, lightPos1.y, lightPos1.z);
        camera.Matrix(shaderProgram, "camMatrix");
        brickTex.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        lightShader.Activate();
        glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
        glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        camera.Matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        lightShader1.Activate();
        glUniformMatrix4fv(glGetUniformLocation(lightShader1.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel1));
        glUniform4f(glGetUniformLocation(lightShader1.ID, "lightColor"), lightColor1.x, lightColor1.y, lightColor1.z, lightColor1.w);
        camera.Matrix(lightShader1, "camMatrix");
        lightVAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    lightVAO1.Delete();
    lightVBO1.Delete();
    lightEBO1.Delete();
    brickTex.Delete();
    shaderProgram.Delete();
    lightShader.Delete();
    lightShader1.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}