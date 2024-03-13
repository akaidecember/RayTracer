#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "color.h"
#include "hittable.h"
#include "material.h"

#include <iostream>

class camera {
    public:
        double aspect_ratio = 1.0;  
        int img_w = 100;  
        int samples_per_pixel = 10;
        int max_recursion_depth = 10;
        double vfov = 90;
        point3 lookfrom = point3(0,0,-1);  
        point3 lookat = point3(0,0,0);  
        vec3 vup = vec3(0,1,0);
        double defocus_angle = 0;
        double focus_dist = 10;

        void render(const hittable& world){
            initialize();
            std::cout << "P3" << std::endl << img_w << ' ' << img_h << std::endl << "255" << std::endl;
            for (int j = 0; j < img_h; ++j){
                std::clog << "\rScanlines remaining: " << (img_h - j) << ' ' << std::flush;
                for (int i = 0; i < img_w; ++i) {
                    color pixel_color(0,0,0);
                    for (int sample = 0; sample < samples_per_pixel; ++sample) {
                        ray r = get_ray(i, j);
                        pixel_color += ray_col(r, world, max_recursion_depth);
                    }
                    write_color(std::cout, pixel_color, samples_per_pixel);
                }
            }
            std::clog << "\rDone." << std::endl;
        }
        
    private:
        int img_h;                   // Rendered image height
        point3 center;               // Camera center
        point3 pixel00_loc;          // Location of pixel 0,0
        vec3 pixel_delta_u, pixel_delta_v;          
        vec3 u,v,w;                  // Camera frame vectors
        vec3 defocus_disk_u, defocus_disk_v;

        void initialize(){
            img_h = static_cast<int>(img_w / aspect_ratio);
            if(img_h < 1){
                img_h = 1;
            }

            center = lookfrom;

            // Determine viewport dimensions
            // auto focal_length = (lookfrom - lookat).length();
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2 * h * focus_dist;
            // auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (static_cast<double>(img_w)/img_h);

            // Calculate the u,v,w 
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            // Calculate the vectors vertical viewport edges
            vec3 viewport_u = viewport_width * u;   
            vec3 viewport_v = viewport_height * (-v);

            // Calculate the horizontal and vertical delta vectors from pixel to pixel
            pixel_delta_u = viewport_u / img_w;
            pixel_delta_v = viewport_v / img_h;

            // Calculate the location of the upper left pixel
            auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

            auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
            defocus_disk_u = u * defocus_radius;
            defocus_disk_v = v * defocus_radius;
        }

        point3 defocus_disk_sample() const{
            auto p = random_in_unit_disk();
            return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
        }

        color ray_col(const ray& r, const hittable& world, int depth) const{
            hit_record rec;
            if(depth <= 0){
                return color(0,0,0);
            }
            if (world.hit(r, interval(0.001, infinity), rec)) {
                ray scattered;
                color attenuation;
                if (rec.mat->scatter(r, rec, attenuation, scattered)){
                    return attenuation * ray_col(scattered, world, depth-1);
                }
                return color(0,0,0);
            }
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
        }

        ray get_ray(int i, int j) const{
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto pixel_sample = pixel_center + pixel_sample_square();
            auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
            auto ray_direction = pixel_sample - ray_origin;
            return ray(ray_origin, ray_direction);
        }

        vec3 pixel_sample_square() const{
            // Returns a random point in the square surrounding a pixel at the origin
            auto px = -0.5 + random_double();
            auto py = -0.5 + random_double();
            return (px * pixel_delta_u) + (py * pixel_delta_v);
        }
};

#endif