#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class ray {
    public:
        ray() {}
        ray(const point3& origin, const vec3& direction)
            : orig(origin), dir(direction)
        {}

        // getter functions:
    
        point3 origin() const  { return orig; }
        vec3 direction() const { return dir; }

        // P(t) = A + tb where A = origin, t = the "index" of the ray, and b = direction
        point3 at(double t) const {
            return orig + t*dir;
        }

    private:
        point3 orig;
        vec3 dir;
};

#endif
