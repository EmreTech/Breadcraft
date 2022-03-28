#pragma once

#include <glad/glad.h>

#include <vector>

namespace gl
{

struct VertexArray
{
    VertexArray() = default;
    ~VertexArray();

    VertexArray(VertexArray&& other);
    VertexArray& operator=(VertexArray&& other);

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    void create();
    void destroy();

    void bind() const;
    void draw(GLenum draw = GL_TRIANGLES) const;

    void addVertexBuffer(int mag, const std::vector<unsigned int>& data);
    void addVertexBuffer(int mag, const std::vector<float>& data);
    void addIndexBuffer(const std::vector<unsigned int>& indices);

    private:
    void reset();

    std::vector<unsigned int> buffers;
    unsigned int id;
    int indicesCount;
};

} // namespace gl
