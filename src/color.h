#ifndef COLOR_H
#define COLOR_H

#include "vec.h"
#include "interval.h"
#include <algorithm>

#define RGB_CONSTANT 256

using color = vec3;

inline double linear_to_gamma(double linear_component){
    if(linear_component > 0) {
        return std::sqrt(linear_component);
    }

    return 0;
}

//takes a array of x, y and z value to find the colour rgb value in that pixel within the screen
void write_color(std::ostream& out, const color& pixel_colour) {

    //Extracts each value from an array within the vec3 object
    double r = pixel_colour.x();
    double g = pixel_colour.y();
    double b = pixel_colour.z();

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const interval intesity(0.000,0.999);
    int rbyte = int(RGB_CONSTANT * std::clamp(r,intesity.min, intesity.max));
    int gbyte = int(RGB_CONSTANT * std::clamp(g,intesity.min, intesity.max));
    int bbyte = int(RGB_CONSTANT * std::clamp(b,intesity.min, intesity.max));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif