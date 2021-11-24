#pragma once

#include <glad/glad.h>

#include <string>

namespace gl
{

struct Texture2D
{
    Texture2D() = default;
    ~Texture2D();

    void create();
    void destroy();

    void bind() const;
    void loadImage(const std::string &file);

    private:
    unsigned int id;
};

} // namespace gl
