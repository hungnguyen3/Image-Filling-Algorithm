#include "fadeColorPicker.h"

fadeColorPicker::fadeColorPicker(double fade)
{
    /* your code here */
    fadeFactor = fade;
}

HSLAPixel fadeColorPicker::operator()(point p)
{
    /* your code here */
    HSLAPixel ret;

    // h and s stay the same
    ret.h = p.c.color.h;
    ret.s = p.c.color.s;

    // convert to type ints
    int x = (double)p.x - (double)p.c.x;
    int y = (double)p.y - (double)p.c.y;

    // decay the luminance of the point p
    ret.l = p.c.color.l * pow(fadeFactor, sqrt(x*x + y*y));
    return ret;
}
