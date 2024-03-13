#ifndef VEC3_H
#define VEC3_H

#include<cmath>
#include<iostream>

class vec3{
    public:
        double e[3];

        // Constructors
        vec3(){
            e[0] = 0;
            e[1] = 0;
            e[2] = 0;
        }
        vec3(double e1, double e2, double e3){
            e[0] = e1;
            e[1] = e2;
            e[2] = e3;
        }

        // Functions
        double x(){
            return e[0];
        }
        double y(){
            return e[1];
        }
        double z(){
            return e[2];
        }

        // Operator overloading
        vec3 operator-() const{
            return vec3(-e[0], -e[1], -e[2]);
        }
        double operator[](int i) const{
            return e[i];
        }
        double& operator[](int i){
            return e[i];
        }
        vec3& operator+=(const vec3 &v){
            // Recall 
            // * -> value at address
            // & -> address of operator
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }
        vec3& operator*=(const vec3 &v){
            // Recall 
            // * -> value at address
            // & -> address of operator
            e[0] *= v.e[0];
            e[1] *= v.e[1];
            e[2] *= v.e[2];
            return *this;
        }
        vec3& operator/=(double t){
            vec3 temp(1/t, 1/t, 1/t);
            *this *= temp;
            return *this;
        }

        double length() const{
            return std::sqrt(length_squared());
        }

        double length_squared() const{
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        bool near_zero() const{
            auto s = 1e-8;
            return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        }

        static vec3 random(){
            return vec3(random_double(), random_double(), random_double());
        }

        static vec3 random(double min, double max){
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }
};

// This is just an alias for vec3, easier to distinguish, but the same thing
using point3 = vec3;

// Vector utility functions
inline std::ostream& operator<<(std::ostream &out, const vec3 &v){
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v){
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v){
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v){
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v){
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t){
    return t * v;
}

inline vec3 operator/(vec3 v, double t){
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v){
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v){
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v){
    return v / v.length();
}

inline vec3 random_in_unit_disk(){
    while(true){
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if(p.length_squared() < 1){
            return p;
        }
    }
}

inline vec3 random_in_unit_sphere(){
    while(true){
        auto p = vec3::random(-1,1);
        if(p.length_squared() < 1){
            return p;
        }
    }
}

inline vec3 random_unit_vector(){
    return unit_vector(random_in_unit_sphere());
}

inline vec3 random_on_hemisphere(const vec3 &normal){
    vec3 on_unit_sphere = random_unit_vector();
    // The dot product with the normal should be 0. else in the wrong one
    if(dot(on_unit_sphere, normal) > 0.0){
        return on_unit_sphere;
    }
    else{
        return -on_unit_sphere;
    }
}

inline vec3 reflect(const vec3 &v, const vec3 &n){
    return v - 2 * dot(v,n) * n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif