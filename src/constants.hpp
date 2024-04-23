constexpr int CHUNK_SIDE = 16;
constexpr int CHUNK_HEIGHT = 64;
constexpr int CHUNK_AREA = CHUNK_SIDE * CHUNK_SIDE;
constexpr int CHUNK_VOLUME = CHUNK_AREA * CHUNK_HEIGHT;

constexpr int VISIBLE_CHUNKS_DISTANCE = 7;
constexpr int WORLD_SIZE = VISIBLE_CHUNKS_DISTANCE + 2;
constexpr int HALF_WORLD_SIZE = WORLD_SIZE / 2;
constexpr int WORLD_AREA = WORLD_SIZE * WORLD_SIZE;
constexpr int MAX_RAYCAST_DIST = 10;