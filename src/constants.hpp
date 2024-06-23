#pragma once

inline constexpr int MAX_BLOCKS_COUNT =            256;

inline constexpr int CHUNK_SIDE =                  16;
inline constexpr int CHUNK_HEIGHT =                64;
inline constexpr int H_CHUNK_SIDE =                CHUNK_SIDE / 2;
inline constexpr int H_CHUNK_HEIGHT =              CHUNK_HEIGHT / 2;
inline constexpr int CHUNK_AREA =                  CHUNK_SIDE * CHUNK_SIDE;
inline constexpr int CHUNK_VOLUME =                CHUNK_AREA * CHUNK_HEIGHT;

inline constexpr int VISIBLE_CHUNKS_DISTANCE =     10;
inline constexpr int VISIBLE_CHUNKS_DIAMETER =     VISIBLE_CHUNKS_DISTANCE * 2 + 1;

inline constexpr int WORLD_SIZE =                  VISIBLE_CHUNKS_DIAMETER + 2;
inline constexpr int HALF_WORLD_SIZE =             WORLD_SIZE / 2;
inline constexpr int WORLD_AREA =                  WORLD_SIZE * WORLD_SIZE;

inline constexpr int MAX_RAYCAST_DIST =            10;
inline constexpr int MESH_BUILDING_PER_FRAME =     8;

inline constexpr float V_MOUSE_SENSETIVITY =       0.002f;
inline constexpr float H_MOUSE_SENSETIVITY =       0.003f;

inline constexpr bool PLAYER_COLLISION =           true;
