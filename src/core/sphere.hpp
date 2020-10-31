#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable { //Inherit from the hittable class
    public:
        sphere() {}
        sphere(point3 cen, double r, shared_ptr<material> m)
        : center(cen), radius(r), mat_ptr(m) {};
    

        virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const override;
    public:
        point3 center; // The center of the sphere
        double radius; // The radius of the sphere
        shared_ptr<material> mat_ptr;
    
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    // Equation: (b^2)x^2 + (-2b(A - C))x + (A - C)(A - C) - r^2 = 0
    // Where:
    // A is the Origin of the ray
    // C is the Center of the sphere
    // r is the Radius of the sphere
    // b is r.direction in the code below
           
    // The Quadratic formula finds x where: ax^2 + bx + c = 0
    // The Quadratic formula is in the resources folder
    
    vec3 oc = r.origin() - center;
    
    auto a = r.direction().length_squared(); // this is (b^2)
    auto half_b = dot(oc, r.direction()); // this is b(A - C) we factor out the two
    auto c = oc.length_squared() - radius*radius; // this is (A - C)(A - C) - r^2
    auto discriminant = half_b*half_b - a*c; // this is the same thing as b^2 - 4ac

    if (discriminant > 0) { // Only do this code if there is a solution (sqrt of a negative number is undefined)
        auto root = sqrt(discriminant);

        auto temp = (-half_b - root) / a; // One quadratic solution (bc of the +/- part)
        if (temp < t_max && temp > t_min) { // if our t is within the min and max t
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius; // The outward normal is always pointing out
            // outward normal = (P - C) we divide it the radius to make it a unit vector
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }

        temp = (-half_b + root) / a; // The other quadratic solution (bc of the +/- part)
        if (temp < t_max && temp > t_min) {
            rec.t = temp; // t and temp are the same
            rec.p = r.at(rec.t); // p is the point of contact
            vec3 outward_normal = (rec.p - center) / radius; // Above
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }

    return false;
}


#endif
