#ifndef _ZOOM_H_
#define _ZOOM_H_

// Struct to store our data
struct Zoom
{
    int x{0};
    int y{0};
    double scale{0.0};

    // Ths structs constructor
    Zoom(int x, int y, double scale): x{x}, y{y}, scale{scale} {}
};

#endif /* _ZOOM_H_ */
