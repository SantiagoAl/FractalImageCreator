#include <iostream>
#include "FractalCreator.h"
#include "Zoom.h"

int main(void)
{
    int height = 600;
    int width = 800;

    FractalCreator fractalCreator(width, height);

    fractalCreator.addRange(0.0, RGB(0, 0, 0));
    fractalCreator.addRange(0.3, RGB(255, 0, 0));
    fractalCreator.addRange(0.5, RGB(255, 255, 0));
    fractalCreator.addRange(1.0, RGB(255, 255, 255));

    fractalCreator.addZoom(Zoom(236, 532, 0.1));
    fractalCreator.run("test.bmp");

    std::cout << "Finished" << std::endl;

    return 0;
}
