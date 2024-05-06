#include "WorldFiles.hpp"

#include <fstream>
#include <filesystem>
#include <cstring>
#include <string>

#include "Chunk.hpp"


inline const std::string SAVES_FOLDER = "../res/saves/";

inline std::string getPath(int cx, int cz) noexcept
{
    return SAVES_FOLDER + std::to_string(cx) + "_" + std::to_string(cz) + ".bin";
}

inline std::string getPath(ChunkPosition pos) noexcept
{
    return SAVES_FOLDER + std::to_string(pos.x) + "_" + std::to_string(pos.z) + ".bin";
}


bool WorldFiles::exists(int cx, int cz) const
{
    return std::filesystem::exists(getPath(cx, cz));
}

bool WorldFiles::save(const Chunk& chunk) const
{
    std::ofstream file(getPath(chunk.getPosition()), std::ios::binary | std::ios::trunc);

    if (!file.is_open())
        return false;

    const voxel_t* const voxels = chunk.getConstData();

    voxel_t currentId = voxels[0];
    uint32_t count = 1;

    for (int i = 1; i < CHUNK_VOLUME; ++i)
    {
        if (voxels[i] == currentId)
        {
            ++count;
            continue;
        }


        file.write(reinterpret_cast<char*>(&currentId), sizeof(voxel_t));
        file.write(reinterpret_cast<char*>(&count), sizeof(uint32_t));

        currentId = voxels[i];
        count = 1;
    }

    // we must write the last set of blocks (usually air)
    file.write(reinterpret_cast<char*>(&currentId), sizeof(voxel_t));
    file.write(reinterpret_cast<char*>(&count), sizeof(uint32_t));

    file.close();

    return true;
}

bool WorldFiles::load(Chunk& chunk) const
{
    std::ifstream file(getPath(chunk.getPosition()), std::ios::binary);

    if (!file.is_open())
        return false;

    voxel_t* const voxels = chunk.getData();

    voxel_t currentId = 0;
    uint32_t count = 1;
    uint32_t offset = 0;

    while (file.read(reinterpret_cast<char*>(&currentId), sizeof(voxel_t)) &&
           file.read(reinterpret_cast<char*>(&count), sizeof(uint32_t)))
    {
        memset(voxels + offset, currentId, count * sizeof(voxel_t));
        offset += count;
    }

    file.close();

    return true;
}
