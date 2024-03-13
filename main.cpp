#include "rtweekend.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "color.h"
#include "material.h"

int main() {
    hittable_list world;                                        // List of hittable objects in the world
    // auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    // auto material_center = make_shared<dielectric>(1.5);
    // auto material_left   = make_shared<dielectric>(1.5);
    // auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);
    // auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    // auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    // auto material_left   = make_shared<dielectric>(1.5);
    // auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);
    // world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    // world.add(make_shared<sphere>(point3( 0.0, 0.0, -1.0), 0.5, material_center));
    // world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    // world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),  -0.4, material_left));
    // world.add(make_shared<sphere>(point3( 1.0, 0.0, -1.0), 0.5, material_right));
    // world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    // world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);
    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),  -0.4, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    // auto R = cos(pi/4);
    // auto material_left  = make_shared<lambertian>(color(0,0,1));
    // auto material_right = make_shared<lambertian>(color(1,0,0));
    // world.add(make_shared<sphere>(point3(-R, 0, -1), R, material_left));
    // world.add(make_shared<sphere>(point3( R, 0, -1), R, material_right));
    camera cam;                                                 // Camera object
    cam.aspect_ratio = 16.0 / 9.0;
    cam.img_w  = 1920;
    cam.samples_per_pixel = 100;
    cam.max_recursion_depth = 50;
    cam.vfov = 20;
    cam.lookfrom = point3(-2,2,1);
    cam.lookat = point3(0,0,-1);
    cam.vup = vec3(0,1,0);
    cam.render(world);                                          // Attach the world object to the camera
}