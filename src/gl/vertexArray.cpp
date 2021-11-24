#include <gl/vertexArray.hpp>

#include <iostream>

namespace
{

unsigned int genBuffer(GLenum type)
{
    unsigned int id;
    glGenBuffers(1, &id);
    glBindBuffer(type, id);
    return id;
}

template <typename T>
void bufferData(const std::vector<T>& data, GLenum type)
{
    glBufferData(type, data.size() * sizeof(T), &data.front(),
                         GL_STATIC_DRAW);
}

void vertexAttribPointer(GLuint index, GLint mag, GLenum type)
{
    glVertexAttribPointer(index, mag, type, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(index);
}

void vertexAttribIntPointer(GLuint index, GLint mag, GLenum type)
{
    glVertexAttribIPointer(index, mag, type, 0, (GLvoid*)0);
    glEnableVertexAttribArray(index);
}

} // namespace


namespace gl
{

void VertexArray::create()
{
    if (!id)
    {
        glGenVertexArrays(1, &id);
    }
}

void VertexArray::destroy()
{
    glDeleteVertexArrays(1, &id);
    glDeleteBuffers(buffers.size(), buffers.data());
    reset();
}

VertexArray::~VertexArray()
{
    destroy();
}

VertexArray::VertexArray(VertexArray&& other)
{
    *this = std::move(other);
}

VertexArray& VertexArray::operator=(VertexArray&& other)
{
    destroy();
    buffers = std::move(other.buffers);
    id = other.id;
    indicesCount = other.indicesCount;
    other.reset();
    return *this;
}

void VertexArray::bind() const
{
    glBindVertexArray(id);
}

void VertexArray::draw(GLenum draw) const
{
    glDrawElements(draw, indicesCount, GL_UNSIGNED_INT, nullptr);
}

void VertexArray::addVertexBuffer(int mag, const std::vector<unsigned int>& data)
{
    bind();
    unsigned int id = genBuffer(GL_ARRAY_BUFFER);
    bufferData(data, GL_ARRAY_BUFFER);
    vertexAttribIntPointer(buffers.size(), mag, GL_UNSIGNED_INT);
    buffers.push_back(id);
}

void VertexArray::addVertexBuffer(int mag, const std::vector<float>& data)
{
    bind();
    unsigned int id = genBuffer(GL_ARRAY_BUFFER);
    bufferData(data, GL_ARRAY_BUFFER);
    vertexAttribPointer(buffers.size(), mag, GL_FLOAT);
    buffers.push_back(id);
}

void VertexArray::addIndexBuffer(const std::vector<unsigned int>& indices)
{
    bind();
    unsigned int id = genBuffer(GL_ELEMENT_ARRAY_BUFFER);
    bufferData(indices, GL_ELEMENT_ARRAY_BUFFER);
    buffers.push_back(id);
    indicesCount = indices.size();
}

void VertexArray::reset()
{
    buffers.clear();
    id = 0;
    indicesCount = 0;
}

} // namespace gl
