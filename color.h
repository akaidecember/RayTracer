#ifndef COLOR_H
#define COLOR_H

#include"vec3.h"
#include<iostream>
#include<fstream> // Include the necessary header file for std::ofstream

using color = vec3;

void write_color(std::ostream &out, color pix_col){
    out << static_cast<int>(255.999 * pix_col.x()) << ' '
    << static_cast<int>(255.999 * pix_col.y()) << ' '
    << static_cast<int>(255.999 * pix_col.z()) << std::endl;
}

#endif