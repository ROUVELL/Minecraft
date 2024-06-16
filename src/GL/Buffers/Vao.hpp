#pragma once

#include "../../typedefs.hpp"


enum class attr_type : u32
{
    FLOAT = 0x1406,
    UNSIGNED_INT = 0x1405
};


class Vao final
{
    u32 ID = 0;

public:
    Vao() noexcept;
    Vao(const Vao&) = default;
    Vao(Vao&&) = default;
    ~Vao() = default;
    
    b8 isAttrEnabled(u8 index) const noexcept;

    u32 getID() const noexcept { return ID; }

    void bindVBO(u32 vboId, u32 stride, u32 binding = 0) noexcept;
    void bindEBO(u32 eboId) noexcept;

    void setAttrData(u8 index, u8 size, u32 offset, attr_type type = attr_type::FLOAT, u32 binding = 0) noexcept;
    void enableAttr(u8 index) noexcept;
    void disableAttr(u8 index) noexcept;

    void setAttrDivisor(u8 index, u8 divisor) noexcept;
    void setBindingDivisor(u32 binding, u8 divisor) noexcept;

    void draw(u32 count, u32 mode = 0x0004, u32 instances = 1) const noexcept;
    void drawElements(u32 count, const u32* indices = nullptr, u32 mode = 0x0004, u32 instances = 1) const noexcept;

    void bind() const noexcept;
    void unbind() const noexcept;
    void del() noexcept;
};