#pragma once

#include "../../typedefs.hpp"


enum class buffer_usage
{
    STREAM_DRAW = 0x88E0,
    STREAM_READ = 0x88E1,
    STREAM_COPY = 0x88E2,
    STATIC_DRAW = 0x88E4,
    STATIC_READ = 0x88E5,
    STATIC_COPY = 0x88E6,
    DYNAMIC_DRAW = 0x88E8,
    DYNAMIC_READ = 0x88E9,
    DYNAMIC_COPY = 0x88EA
};

enum class buffer_access
{
    READ_ONLY =  0x88B8,
    WRITE_ONLY = 0x88B9,
    READ_WRITE = 0x88BA
};


class Buffer final
{
    u32 ID = 0;

public:
    Buffer() noexcept;
    Buffer(const Buffer&) = default;
    Buffer(Buffer&&) = default;
    ~Buffer() = default;

    b8 isMapped() const noexcept;

    u32 getID() const noexcept { return ID; }
    u64 getSize() const noexcept;

    void create(const void* bytes, u64 size, buffer_usage usage = buffer_usage::STATIC_DRAW) noexcept;
    void del() noexcept;

    void copyFrom(const Buffer& buffer, u64 size, u64 srcOffset = 0, u64 dstOffset = 0) noexcept;
    void write(const void* bytes, u64 size, u64 offset = 0) noexcept;
    void read(void* bytes, u64 size, u64 offset = 0) const noexcept;

    void* map(buffer_access access) noexcept;
    void getMappedData(void** ptr) noexcept;
    void unmap() noexcept;
};