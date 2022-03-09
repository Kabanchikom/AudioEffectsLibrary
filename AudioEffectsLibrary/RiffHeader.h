#pragma once
#include "WavHeader.h"
struct RiffHeader : WavHeader
{
    char format[4];      // WAVE Header      
};

