#include "ZoomList.h"

// The class constructor
ZoomList::ZoomList(int width, int height): m_width{width}, m_height{height} {}

// Store the zoom in the ZoomList
void ZoomList::add(const Zoom &zoom)
{
    zooms.push_back(zoom);

    // This will calculate the distance of the x-coordinate the user has
    // selected to zoom around from to the center of the fractal
    m_xCenter += (zoom.x - m_width / 2) * m_scale;

    // Same as above
    m_yCenter += (zoom.y - m_height / 2) * m_scale;

    // Here, we calculate the combined scale. It is a new scale using the scale
    // specified in 'zoom.h'
    m_scale *= zoom.scale;
}

// Function that maps from the bitmap coordinates to the actual fractal
// coordinates
std::pair<double, double> ZoomList::doZoom(int x, int y)
{
    double xFractal = (x - m_width / 2) * m_scale + m_xCenter;
    double yFractal = (y - m_height / 2) * m_scale + m_yCenter;

    return std::pair<double, double>(xFractal, yFractal);
}
