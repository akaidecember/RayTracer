#include "rtweekend.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"

int main() {
    hittable_list world;                                        // List of hittable objects in the world
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
    camera cam;                                                 // Camera object
    cam.aspect_ratio = 16.0 / 9.0;
    cam.img_w  = 400;
    cam.samples_per_pixel = 100;
    cam.render(world);                                          // Attach the world object to the camera
}