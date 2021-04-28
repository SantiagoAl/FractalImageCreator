#include <fstream>
#include "Bitmap.h"
#include "BitMapInfoHeader.h"
#include "BitMapFileHeader.h"

// The class constructor
Bitmap::Bitmap(int width, int height)
    : m_width{width}, m_height{height},
        m_Pixels(new std::uint8_t[width * height * 3]{}) {}

bool Bitmap::write(std::string filename)
{
    BitMapFileHeader fileHeader;
    BitMapInfoHeader infoHeader;

    fileHeader.fileSize = sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)
                            + (m_width * m_height * 3);
    fileHeader.dataOffset = sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader);

    infoHeader.width = m_width;
    infoHeader.height = m_height;

    std::ofstream outputFile;
    outputFile.open(filename, std::ios::out|std::ios::binary);

    if (!outputFile)
        return false;

    outputFile.write((char *)&fileHeader, sizeof(fileHeader));
    outputFile.write((char *)&infoHeader, sizeof(infoHeader));
    // Here, the 'get()' method gets us the raw pointer behind the unique_ptr,
    // then we can cast it to a char pointer
    outputFile.write((char *)m_Pixels.get(), m_width * m_height * 3);

    // Close the outputFile. Not closing the file could cause some serious
    // problems
    outputFile.close();

    // Here, I check again to see if there are some errors. If we were not able
    // to close the file then something probably went wrong when writing to
    // the output file
    if (!outputFile)
        return false;

    return true;
}

// This function will set the pixels in the fractal image
void Bitmap::setPixel(int x, int y, std::uint8_t red, std::uint8_t green,
                        std::uint8_t blue)
{
    std::uint8_t *pixel = m_Pixels.get();

    pixel += (y * 3 * m_width + x * 3);

    pixel[0] = blue;
    pixel[1] = green;
    pixel[2] = red;
}

// The class destructor
Bitmap::~Bitmap() {}
