#pragma once

inline constexpr int CHUNK_SIDE =                  16;
inline constexpr int CHUNK_HEIGHT =                64;
inline constexpr int CHUNK_AREA =                  CHUNK_SIDE * CHUNK_SIDE;
inline constexpr int CHUNK_VOLUME =                CHUNK_AREA * CHUNK_HEIGHT;

inline constexpr int VISIBLE_CHUNKS_DISTANCE =     7;
inline constexpr int WORLD_SIZE =                  VISIBLE_CHUNKS_DISTANCE + 2;
inline constexpr int HALF_WORLD_SIZE =             WORLD_SIZE / 2;
inline constexpr int WORLD_AREA =                  WORLD_SIZE * WORLD_SIZE;
inline constexpr int MAX_RAYCAST_DIST =            10;