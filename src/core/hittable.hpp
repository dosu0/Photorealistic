#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "main.hpp"
#include "ray.hpp"

class material;

struct hit_record { // A Mini ds for containing info about the hit of a surface
    point3 p;       // The point of contact
    vec3 normal;    // Don't know
    double t;       // The "t" that satisfies this equation: P(t) = A + tb
    bool front_face;
    shared_ptr<material> mat_ptr;
    
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        // If the ray directions are the same "dot(r.direction(), outward_normal)" will be positive
        // If the ray directions are not the same "dot(r.direction(), outward_normal)" will be negative
        // If they are different (negative) it is outside otherwise it is inside the surface
        front_face = dot(r.direction(), outward_normal) < 0;
        
        if (front_face)
        {
            // ray is outside the sphere
            normal = outward_normal; // keep it the same
        }
        else
        {
            //ray inside the sphere
            normal = -outward_normal; // flip the normal
        }
        
        //normal = front_face ? outward_normal :-outward_normal; BS
    }
};

class hittable {
    public:
        virtual bool hit // It is "virtual" because the hit function will be defined in children of this class
        (
            const ray& r,   // reference to the ray
            double t_min,   // minimum value of t
            double t_max,   // maximum value of t
            hit_record& rec // a reference to hit record
        )
        const = 0;
};

#endif
