#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
class Fragment {
public:
    const char* getFrag(std::string ambient)  { return fragmentShader; };
private:
    const char* fragmentShader;

};