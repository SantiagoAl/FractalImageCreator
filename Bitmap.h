#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <string>
#include <cstdint>
#include <memory>

class Bitmap
{
private:
    int m_width{0};
    int m_height{0};
    std::unique_ptr<std::uint8_t[]> m_Pixels{nullptr};

public:
    // Class Constructor
    Bitmap(int width, int height);

    // This will allow us to set pixels in the bitmap to specify colors
    void setPixel(int x, int y, std::uint8_t red, std::uint8_t green, std::uint8_t blue);

    // This will write the bitmap to a file using the filename passed to the
    // function. It will return 'true' if it succeeds and 'false' otherwise
    bool write(std::string filename);

    // Class Destructor
    virtual ~Bitmap();
};

#endif /* _BITMAP_H_ */
