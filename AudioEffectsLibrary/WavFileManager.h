#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "WavHeader.h"
#include "RiffHeader.h"
#include "FmtHeader.h"
#include "DataHeader.h"
#include "Wav.h"

using namespace std;

/// <summary>
/// Read/write .wav files.
/// </summary>
class WavFileManager
{
public:
    /// <summary>
    /// Read whole .wav file.
    /// </summary>
    /// <param name="path">Path to file.</param>
    Wav ReadAll(const string& path);

    /// <summary>
    /// Read header of .wav file.
    /// </summary>
    /// <param name="file">File stream.</param>
    /// <returns>Header of type T.</returns>
    template<typename T>
    T ReadHeader(ifstream& file);

    /// <summary>
    /// Read data chunk of .wav file.
    /// </summary>
    /// <param name="file">File stream.</param>
    /// <param name="size">Chunk size.</param>
    /// <returns>Array of bytes.</returns>
    vector<char> ReadChunk(ifstream& file, unsigned long size);

    /// <summary>
    /// Check if .wav header has following chunkId.
    /// </summary>
    /// <param name="header">.wav header.</param>
    /// <param name="chunkId">Id to compare.</param>
    bool HasChunkID(const WavHeader& header, const char chunkId[4]);

    /// <summary>
    /// Skip all chunks before reqired chunk.
    /// </summary>
    /// <param name="file">File stream.</param>
    /// <param name="chunkId">Id of required chunk.</param>
    bool TrySkipChunksBefore(ifstream& file, const char chunkId[4]);

    /// <summary>
    /// Write all data into file.
    /// </summary>
    /// <param name="data">Wav to write.</param>
    /// <param name="path">Path to output file.</param>
    void WriteAll(Wav data, const string& path);
};

