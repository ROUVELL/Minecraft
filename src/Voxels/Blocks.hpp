
#include <cstdint>
#include <string>
#include <unordered_map>


using voxel_t = uint8_t;


struct Block
{
    const std::string name;  // unigue string name (air, dirt, grass, ...)

    Block() : name("empty") { }
    Block(const std::string& name) : name(name) { }
};


class Blocks
{
    static std::unordered_map<voxel_t, Block> blocks;

    Blocks() = default;
    ~Blocks() = default;

    static void addBlock(voxel_t id, const std::string& name);

public:
    static void initialize();

    static bool exists(voxel_t id);

    static const Block& getBlock(voxel_t id);
};