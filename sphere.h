#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable{
    public:
        // Constructor
        sphere(point3 center, double radius){
            this->center = center;
            this->radius = radius;
        }
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 oc = r.origin() - center;
            auto a = r.direction().length_squared();
            auto half_b = dot(oc, r.direction());
            auto c = oc.length_squared() - radius * radius;
            auto discr = half_b * half_b - a * c;
            if(discr < 0){
                return false;
            }
            auto sqrtd = sqrt(discr);
            auto root = (-half_b - sqrtd) / a;
            if(!ray_t.surrounds(root)){
                root = (-half_b + sqrtd) / a;
                if (!ray_t.surrounds(root))
                    return false;
            }
            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }
    
    private:
        point3 center;
        double radius;
};

#endif