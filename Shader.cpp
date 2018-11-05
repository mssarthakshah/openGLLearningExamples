/*Implemention class for shaders*/

#include "shader.h"

using namespace std;

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
    string vertexShaderSource;
    string fragShaderSource;

    ifstream vshaderfile;
    ifstream fshaderfile;

    // ensure ifstream objects can throw exceptions:
    vshaderfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fshaderfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vshaderfile.open(vertexPath);
        fshaderfile.open(fragmentPath);
        stringstream vshaderstream, fshaderstream;

        vshaderstream << vshaderfile.rdbuf();
        fshaderstream << fshaderfile.rdbuf();

        vshaderfile.close();
        fshaderfile.close();

        vertexShaderSource = vshaderstream.str();
        fragShaderSource = fshaderstream.str();
    }
    catch(ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_NOT_READ_PROPERLY" << endl;
    }

    const char* vcode = vertexShaderSource.c_str();
    const char* fcode = fragShaderSource.c_str();

    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vcode , NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fcode, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    // check for linking errors
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string & name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID , name.c_str()),(int)value);
}

void Shader::setInt(const std::string & name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);

}

void Shader::setFloat(const std::string & name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
