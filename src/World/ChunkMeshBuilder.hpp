#pragma once

class Chunk;
struct chunk_vertex_t;

void buildChunkMesh(const Chunk& chunk,
                    chunk_vertex_t* vertices,
                    unsigned int* indices,
                    unsigned int& verticesCount,
                    unsigned int& indicesCount);
