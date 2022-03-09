#pragma once
struct WavHeader
{
    char chunkId[4];     // RIFF, FMT, data, e.t.c.
    unsigned long ChunkSize;      // Chunk Size  
};

