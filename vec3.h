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
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v){
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v){
    return v / v.length();
}

#endif