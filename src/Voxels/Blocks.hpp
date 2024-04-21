
#include <cstdint>
#include <unordered_map>


using voxel_t = uint8_t;


struct Block
{
    const voxel_t id;
    const char* name;

    Block() : id(0), name("air") { }
    Block(voxel_t id, const char* name)
        : id(id), name(name) { }
};


class Blocks
{
    static std::unordered_map<voxel_t, Block> blocks;

    Blocks() = default;
    ~Blocks() = default;

    static void addBlock(voxel_t id, const char* name);

public:
    static void initialize();

    static bool exists(voxel_t id);

    static const Block& getBlock(voxel_t id);
};