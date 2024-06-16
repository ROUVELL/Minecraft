#include "Vao.hpp"

#include <GL/glew.h>


Vao::Vao() noexcept
{
    glCreateVertexArrays(1, &ID);
}

b8 Vao::isAttrEnabled(u8 index) const noexcept
{
    GLint flag = GL_FALSE;
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &flag);
    return flag;
}

void Vao::bindVBO(u32 vbo, u32 stride, u32 binding) noexcept
{
    glVertexArrayVertexBuffer(ID, binding, vbo, 0, (i32)stride);
}

void Vao::bindEBO(u32 ebo) noexcept
{
    glVertexArrayElementBuffer(ID, ebo);
}

void Vao::setAttrData(u8 index, u8 size, u32 offset, attr_type type, u32 binding) noexcept
{
    if (type == attr_type::FLOAT)
        glVertexArrayAttribFormat(ID, index, size, (GLenum)type, GL_FALSE, offset);
    else
        glVertexArrayAttribIFormat(ID, index, size, (GLenum)type, offset);

    glVertexArrayAttribBinding(ID, index, binding);
    glEnableVertexArrayAttrib(ID, index);
}

void Vao::enableAttr(u8 index) noexcept
{
    glEnableVertexArrayAttrib(ID, index);
}

void Vao::disableAttr(u8 index) noexcept
{
    glDisableVertexArrayAttrib(ID, index);
}

void Vao::setAttrDivisor(u8 index, u8 divisor) noexcept
{
    glVertexAttribDivisor(index, divisor);
}

void Vao::setBindingDivisor(u32 binding, u8 divisor) noexcept
{
    glVertexArrayBindingDivisor(ID, binding, divisor);
}

void Vao::draw(u32 count, u32 mode, u32 instances) const noexcept
{
    glDrawArraysInstanced((GLenum)mode, 0, count, instances);
}

void Vao::drawElements(u32 count, const u32* indices, u32 mode, u32 instances) const noexcept
{
    glDrawElementsInstanced((GLenum)mode, count, GL_UNSIGNED_INT, indices, instances);
}

void Vao::bind() const noexcept
{
    glBindVertexArray(ID);
}

void Vao::unbind() const noexcept
{
    glBindVertexArray(0);
}

void Vao::del() noexcept
{
    glDeleteVertexArrays(1, &ID);
    ID = 0;
}