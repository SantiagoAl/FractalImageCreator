#ifndef _FRACTALCREATOR_H_
#define _FRACTALCREATOR_H_

#include <string>
#include <cstdint>
#include <memory>
#include <math.h>
#include <vector>
#include "Zoom.h"
#include "Mandelbrot.h"
#include "Bitmap.h"
#include "ZoomList.h"
#include "RGB.h"

class FractalCreator
{
private:
    int m_width;
    int m_height;
    int m_total;

    bool m_bGotFirstRange{false};

    std::vector<int> ranges;
    std::vector<RGB> colors;
    std::vector<int> rangeTotals;

    // This will help to build a histogram of the number of iterations
    std::unique_ptr<int[]> m_histogram;
    std::unique_ptr<int[]> m_fractal;

    Bitmap m_bitmap;

    ZoomList m_zoomList;

private:
    void calculateIterations();
    void calculateTotalIterations();
    void calculateRangeTotals();
    void drawFractal();
    void writeBitmap(std::string filename);
    int getRange(int iterations) const;

public:
    FractalCreator(int width, int height);

    void addRange(double rangeEnd, const RGB &rgb);
    void addZoom(const Zoom &zoom);
    void run(std::string filename);

    virtual ~FractalCreator();
};

#endif /* _FRACTALCREATOR_H_ */
