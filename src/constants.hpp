#pragma once

inline constexpr const int MAX_BLOCKS_COUNT =            256;

inline constexpr const int CHUNK_SIDE =                  16;
inline constexpr const int CHUNK_HEIGHT =                64;
inline constexpr const int H_CHUNK_SIDE =                CHUNK_SIDE / 2;
inline constexpr const int H_CHUNK_HEIGHT =              CHUNK_HEIGHT / 2;
inline constexpr const int CHUNK_AREA =                  CHUNK_SIDE * CHUNK_SIDE;
inline constexpr const int CHUNK_VOLUME =                CHUNK_AREA * CHUNK_HEIGHT;

inline constexpr const int VISIBLE_CHUNKS_DISTANCE =     2;
inline constexpr const int VISIBLE_CHUNKS_DIAMETER =     VISIBLE_CHUNKS_DISTANCE * 2 + 1;

inline constexpr const int WORLD_SIZE =                  VISIBLE_CHUNKS_DIAMETER + 2;
inline constexpr const int HALF_WORLD_SIZE =             WORLD_SIZE / 2;
inline constexpr const int WORLD_AREA =                  WORLD_SIZE * WORLD_SIZE;

inline constexpr const int MAX_RAYCAST_DIST =            10;
inline constexpr const int MESH_BUILDING_PER_FRAME =     8;

inline constexpr const float V_MOUSE_SENSETIVITY =       0.002f;
inline constexpr const float H_MOUSE_SENSETIVITY =       0.003f;

inline constexpr const bool PLAYER_COLLISION =           false;
