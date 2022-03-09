#pragma once
#include "WavHeader.h"
#include "RiffHeader.h"
#include "FmtHeader.h"
#include "DataHeader.h"
#include <vector>

struct Wav
{
    RiffHeader RiffHeader;
    FmtHeader FmtHeader;
    DataHeader DataHeader;
    std::vector<char> Data;
};

