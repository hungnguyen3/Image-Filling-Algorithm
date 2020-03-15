#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(unsigned int borderSize, HSLAPixel fillColor, PNG &img, double tolerance)
{
    /* your code here */
    border = borderSize;
    color = fillColor;
    im = img;
    tol = tolerance;
}

HSLAPixel borderColorPicker::operator()(point p)
{
    // convert all unsigned to int
    int x = p.x;
    int y = p.y;
    int size = border;
    
    // only loop through a circumference aroudn the point p
    for (int i = x - size ; i <= x + size; i ++) {
        for (int j = y - size ; j <= y + size; j ++) {
            // if its outside of the image but it is within the fill border
            if ((i < 0 || j < 0 || i >= (int)im.width() || j >= (int)im.height()) 
                && ((x - i)*(x -i) + (y - j) * (y - j)) <= size*size) {
                return color;
            }
            // if it is within the image and is is within the fill border
            else if ((((x - i)*(x -i) + (y - j) * (y - j)) <= size*size) 
                    && im.getPixel(i,j)->dist(p.c.color)>tol) {
                return color;
            }
        }
    }
    
    return *im.getPixel(x,y);
}