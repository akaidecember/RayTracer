#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <math.h>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = M_PI;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif