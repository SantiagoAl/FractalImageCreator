#ifndef _MANDELBROT_H_
#define _MANDELBROT_H_

class Mandelbrot
{
public:
    static const int MAX_ITERATIONS = 1000;

public:
    Mandelbrot();

    static int getIterations(double x, double y);

    virtual ~Mandelbrot();
};

#endif /* _MANDELBROT_H_ */
