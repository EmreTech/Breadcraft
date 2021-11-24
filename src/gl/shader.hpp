#pragma once

#include <glad/glad.h>
  
#include <string>

namespace gl
{

struct Shader
{
    unsigned int ID;
    
    Shader() {}
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();

    void init(const std::string &vertexPath, const std::string &fragmentPath);
    void destroy();

    void use();

    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
};

} //namespace gl