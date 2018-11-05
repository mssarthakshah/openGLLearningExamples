/*Class to abstract all the shader program creation logic out of the actual rendering code*/
#pragma once

#ifndef SHADER_H

#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    //program Id
    unsigned int ID;

    //Constructor 
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif // !SHADER_H