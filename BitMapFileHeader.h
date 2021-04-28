#ifndef _BITMAPFILEHEADER_H_
#define _BITMAPFILEHEADER_H_

#include <cstdint>

// This makes C++ align the struct below on 2 byte boundaries. Basically, the
// struct will be left just how it is below and there will be no hidden padding
#pragma pack(push, 2)

struct BitMapFileHeader
{
    char header[2]{'B', 'M'}; // Lets the application know this is a bitmap file
    std::int32_t fileSize; // The size of the final file
    std::int32_t reserved{0};
    std::int32_t dataOffset; // How long into the file the data begins
};

#pragma pack(pop)

#endif /* _BITMAPFILEHEADER_H */
