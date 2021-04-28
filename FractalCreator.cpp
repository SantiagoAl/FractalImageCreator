#include "FractalCreator.h"
#include <assert.h>

// The class constructor
FractalCreator::FractalCreator(int width, int height)
    :m_width{width}, m_height{height}, m_total{0},
    m_histogram{new int[Mandelbrot::MAX_ITERATIONS]{}},
    m_fractal{new int[m_width * m_height]{}}, m_bitmap{m_width, m_height},
    m_zoomList{m_width, m_height}
{
    m_zoomList.add(Zoom(m_width / 2, m_height / 2, 2.0 / m_width));
}

// This will calculate the number of iterations for each pixel
void FractalCreator::calculateIterations()
{
    double scale = 2.0 / m_height;

    // The loop will get the number of iterations for each pixel
    for (int y{0}; y < m_height; y++)
    {
        for (int x{0}; x < m_width; x++)
        {
            std::pair<double, double> coords = m_zoomList.doZoom(x, y);

            int iterations = Mandelbrot::getIterations(coords.first, coords.second);

            m_fractal[y * m_width + x] = iterations;

            if (iterations != Mandelbrot::MAX_ITERATIONS)
                m_histogram[iterations]++;
        }
    }
}

void FractalCreator::calculateRangeTotals()
{
    int rangeIndex{0};

    for (int i{0}; i < Mandelbrot::MAX_ITERATIONS; i++)
    {
        int pixels = m_histogram[i];

        if (i >= ranges[rangeIndex + 1])
        {
            rangeIndex++;
        }

        rangeTotals[rangeIndex] += pixels;
    }
}

void FractalCreator::calculateTotalIterations()
{
    // Get the total number of iterations in the histogram
    for (int i{0}; i < Mandelbrot::MAX_ITERATIONS; i++)
    {
        m_total += m_histogram[i];
    }
}

// Draw the fractal
void FractalCreator::drawFractal()
{
    // This is the main loop that will get the colors for each pixel in the
    // fractal
    for (int y{0}; y < m_height; y++)
    {
        for (int x{0}; x < m_width; x++)
        {
            // Find what color range the pixel is in
            int iterations = m_fractal[y * m_width + x];
            int range = getRange(iterations);

            // Get the total number of pixels in this range
            int rangeTotal = rangeTotals[range];
            int rangeStart = ranges[range];

            // The start color for this range
            RGB  &startColor = colors[range];
            // The end color for this range
            RGB &endColor = colors[range + 1];
            RGB colorDiff = endColor - startColor;

            // First initialize our RGB to zero.
            std::uint8_t red{0};
            std::uint8_t green{0};
            std::uint8_t blue{0};

            // This 'if' statement along with the 'pow' function will have the
            // the effect of giving pixels with a higher number of iterations
            // brighter colors, and pixels with lower number of iterations will
            // be darker, which will exentuate the colors in the fractal
            if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
                int totalPixels{0};

                for (int i = rangeStart; i <= iterations; i++)
                {
                    totalPixels += m_histogram[i];
                }

                red = startColor.r +
                    colorDiff.r * static_cast<double>(totalPixels)/rangeTotal;
                green = startColor.g +
                    colorDiff.g * static_cast<double>(totalPixels)/rangeTotal;;
                blue = startColor.b +
                    colorDiff.b * static_cast<double>(totalPixels)/rangeTotal;;
            }

            m_bitmap.setPixel(x, y, red, green, blue);
        }
    }
}

void FractalCreator::addRange(double rangeEnd, const RGB &rgb)
{
    ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
    colors.push_back(rgb);

    if (m_bGotFirstRange)
    {
        rangeTotals.push_back(0);
    }

    m_bGotFirstRange = true;
}

int FractalCreator::getRange(int iterations) const
{
    int range{0};

    for (int i{1}; i < ranges.size(); i++)
    {
        range = i;

        if (ranges[i] > iterations)
            break;
    }

    range--;

    assert(range > -1);
    assert(range < ranges.size());

    return range;
}

// This function will add a zoom when we want to zoom in on any particular
// point in the image
void FractalCreator::addZoom(const Zoom &zoom)
{
    m_zoomList.add(zoom);
}

// This function will assist with writing to the bitmap
void FractalCreator::writeBitmap(std::string filename)
{
    m_bitmap.write(filename);
}

void FractalCreator::run(std::string filename)
{
    // addZoom(Zoom(236, 532, 0.1));
    calculateIterations();
    calculateTotalIterations();
    calculateRangeTotals();
    drawFractal();
    writeBitmap(filename);
}

// The class destructor
FractalCreator::~FractalCreator() {}
