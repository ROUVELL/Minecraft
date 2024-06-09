#pragma once

class Chunk;

class WorldFiles final
{
public:
    WorldFiles() = default;
    WorldFiles(const WorldFiles&) = default;
    WorldFiles(WorldFiles&&) noexcept = default;
    ~WorldFiles() = default;

    bool exists(int cx, int cz) const;

    bool save(const Chunk& chunk) const;
    bool load(Chunk& chunk) const;
};