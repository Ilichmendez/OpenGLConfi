#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

class Light {
public:
    Light(GLuint indices [], GLfloat vertices[], GLuint indicesFigura[], GLfloat verticesFigura[]);
