
#include<iostream>

#include "color.h"
#include "vec3.h"
#include "ray.h"

/*
There are some things to note in this code:

* The pixels are written out in rows.
* Every row of pixels is written out left to right.
* These rows are written out from top to bottom.
* By convention, each of the red/green/blue components are represented internally 
  by real-valued variables that range from 0.0 to 1.0. These must be scaled to 
  integer values between 0 and 255 before we print them out.
* Red goes from fully off (black) to fully on (bright red) from left to right, and
  green goes from fully off at the top to black at the bottom. Adding red and green 
  light together make yellow so we should expect the bottom right corner to be yellow.
*/

double hit_sphere(const point3& center, double radius, const ray &r){
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discr = half_b * half_b - a * c;
    if(discr < 0){
        return -1.0;
    }
    else{
        return (-half_b - std::sqrt(discr) / (a));
    }
}

color ray_col(const ray& r){
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if(t > 0.0){
        vec3 N  = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    vec3 unit_dir = unit_vector(r.direction());
    auto a = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main(){

    auto aspect_ratio = 16.0 / 9.0;
    int img_w = 400;

    // Given the aspect ratio, we will calculate the height
    int img_h = static_cast<int>(img_w / aspect_ratio);
    if(img_h < 0){
        img_h = 1;
    }

    // Camera
    auto focal_len = 1.0;
    auto camera_center = point3(0,0,0);

    // Calculating the viewport width
    auto viewport_h = 2.0;
    auto viewport_w = viewport_h * (static_cast<double>(img_w)/img_h);

    auto viewport_u = vec3(viewport_w, 0, 0);
    auto viewport_v = vec3(0, -viewport_h, 0);

    auto pixel_del_u = viewport_u / img_w;
    auto pixel_del_v = viewport_v / img_h;

    // Location of upper-eft pixel
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_len) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_del_u + pixel_del_v);

    std::cout << "P3" << std::endl << img_w << ' ' << img_h << std::endl << "255" << std::endl;

    // Using j first because it's height, with usually corresponds to j
    for(int j = 0; j < img_h; ++j){
        std::clog << "\rScanlines remaining: " << (img_h - j) << ' ' << std::flush;
        for(int i = 0; i < img_w; ++i){
            //auto pix_col = color(double(i)/(img_w - 1), double(j)/(img_h - 1), 0);
            auto pixel_center = pixel00_loc + (i * pixel_del_u) + (j * pixel_del_v);
            auto ray_dir = pixel_center - camera_center;
            ray r(camera_center, ray_dir);
            color pix_col = ray_col(r);
            write_color(std::cout, pix_col);
        }
    }    
    std::clog << "Done." << std::endl;
}