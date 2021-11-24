#include <gl/texture.hpp>

#include <stb_image.h>
#include <iostream>

namespace gl
{

void Texture2D::create()
{
    if (!id)
    {
        glGenTextures(1, &id);
        bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

void Texture2D::destroy()
{
    glDeleteTextures(1, &id);
}

Texture2D::~Texture2D()
{
    destroy();
}

void Texture2D::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture2D::loadImage(const std::string &file)
{
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);

    if (data)
    {
        bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << '\n';
    }
    
    stbi_image_free(data);
}

} // namespace gl
