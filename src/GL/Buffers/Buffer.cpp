#include "Buffer.hpp"

#include "GL/glew.h"


Buffer::Buffer() noexcept
{
    glCreateBuffers(1, &ID);
}

b8 Buffer::isMapped() const noexcept
{
    i32 flag = GL_FALSE;   
    glGetNamedBufferParameteriv(ID, GL_BUFFER_MAPPED, &flag);
    return flag;
}

u64 Buffer::getSize() const noexcept
{
    u64 size = 0;
    glGetNamedBufferParameteriv(ID, GL_BUFFER_SIZE, (i32*)&size);
    return size;
}

void Buffer::create(const void* bytes, u64 size, buffer_usage usage) noexcept
{
    glNamedBufferData(ID, size, bytes, (GLenum)usage);
}

void Buffer::del() noexcept
{
    glDeleteBuffers(1, &ID);
    ID = 0;
}

void Buffer::copyFrom(const Buffer& buffer, u64 size, u64 srcOffset, u64 dstOffset) noexcept
{
    glCopyNamedBufferSubData(buffer.ID, ID, srcOffset, dstOffset, size);
}

void Buffer::write(const void* bytes, u64 size, u64 offset) noexcept
{
    glNamedBufferSubData(ID, offset, size, bytes);
}

void Buffer::read(void* bytes, u64 size, u64 offset) const noexcept
{
    glGetNamedBufferSubData(ID, offset, size, bytes);
}

void* Buffer::map(buffer_access access) noexcept
{
    return glMapNamedBuffer(ID, (GLenum)access);
}

void Buffer::unmap() noexcept
{
    glUnmapNamedBuffer(ID);
}
