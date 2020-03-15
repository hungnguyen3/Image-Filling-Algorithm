#include "solidColorPicker.h"

solidColorPicker::solidColorPicker(HSLAPixel fillColor)
{
    /* your code here */
    color = fillColor;
}

HSLAPixel solidColorPicker::operator()(point p)
{
    /* your code here */
    // return fillColor no matter what
    return color;
}

