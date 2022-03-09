#include "WavFileManager.h"

Wav WavFileManager::ReadAll(const string& path)
{
    ifstream file(path, ios::binary);

    if (!file)
    {
        throw runtime_error("Can't open file: " + path);
    }

    Wav* wavFile = new Wav();

    wavFile->RiffHeader = ReadHeader<RiffHeader>(file);

    string format = wavFile->RiffHeader.format;
    if (format != "WAVE")
    {
        throw runtime_error("Wrong format. File: " + path);
    }

    wavFile->FmtHeader = ReadHeader<FmtHeader>(file);

    if (!TrySkipChunksBefore(file, "data"))
    {
        throw runtime_error("Can't find wav data. File: " + path);
    }

    wavFile->DataHeader = ReadHeader<DataHeader>(file);

    wavFile->Data = ReadChunk(file, wavFile->DataHeader.ChunkSize);
    reverse(wavFile->Data.begin(), wavFile->Data.end());

    file.close();
    return *wavFile;
}

template<typename T>
T WavFileManager::ReadHeader(ifstream& file)
{
    T header;
    int headerSize = sizeof(T);
    file.read((char*)&header, headerSize);
    return header;
}

vector<char> WavFileManager::ReadChunk(ifstream& file, unsigned long size)
{
    vector<char> chunk(size);
    file.read((char*)&chunk[0], size);
    return chunk;
}

bool WavFileManager::HasChunkID(const WavHeader& header, const char chunkId[4])
{
    return ((header.chunkId[0] == chunkId[0]) &&
        (header.chunkId[1] == chunkId[1]) &&
        (header.chunkId[2] == chunkId[2]) &&
        (header.chunkId[3] == chunkId[3]));
}

bool WavFileManager::TrySkipChunksBefore(ifstream& file, const char chunkId[4])
{
    while (!file.eof())
    {
        streampos pos = file.tellg();
        WavHeader header = ReadHeader<WavHeader>(file);
        vector<char> chunk = ReadChunk(file, header.ChunkSize);
        if (HasChunkID(header, chunkId))
        {
            file.clear();
            file.seekg(pos);
            return true;
        }
        chunk.clear();
        chunk.shrink_to_fit();
    }
    return false;
}

void WavFileManager::WriteAll(Wav data, const string& path)
{
    ofstream file(path, ios::binary);
    file.write((char*)&data.RiffHeader, sizeof(RiffHeader));
    file.write((char*)&data.FmtHeader, sizeof(FmtHeader));
    file.write((char*)&data.DataHeader, sizeof(DataHeader));

    reverse(data.Data.begin(), data.Data.end());

    file.write((char*)&data.Data[0], data.DataHeader.ChunkSize);
    file.close();
}