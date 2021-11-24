#pragma once

#include <glad/glad.h>
#include <utils/glm_include.hpp>
  
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

    void set(const std::string &name, bool value) const;  
    void set(const std::string &name, int value) const;   
    void set(const std::string &name, float value) const;
    void set(const std::string &name, const glm::mat4 &val) const;
};

} //namespace gl