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

inline std::string getPath(chunk_pos pos) noexcept
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

    const voxel_id* const voxels = chunk.getConstData();

    voxel_id currentId = voxels[0];
    u32 count = 1;

    for (int i = 1; i < CHUNK_VOLUME; ++i)
    {
        if (voxels[i] == currentId)
        {
            ++count;
            continue;
        }

        file.write(reinterpret_cast<char*>(&currentId), sizeof(voxel_id));
        file.write(reinterpret_cast<char*>(&count), sizeof(u32));

        currentId = voxels[i];
        count = 1;
    }

    // we must write the last set of blocks (usually air)
    file.write(reinterpret_cast<char*>(&currentId), sizeof(voxel_id));
    file.write(reinterpret_cast<char*>(&count), sizeof(u32));

    file.close();

    return true;
}

bool WorldFiles::load(Chunk& chunk) const
{
    std::ifstream file(getPath(chunk.getPosition()), std::ios::binary);

    if (!file.is_open())
        return false;

    voxel_id* const voxels = chunk.getData();

    voxel_id currentId = 0;
    u32 count = 1;
    u32 offset = 0;

    while (file.read(reinterpret_cast<char*>(&currentId), sizeof(voxel_id)) &&
           file.read(reinterpret_cast<char*>(&count), sizeof(u32)))
    {
        memset(voxels + offset, currentId, count * sizeof(voxel_id));
        offset += count;
    }

    file.close();

    return true;
}
