#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "main.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "material.hpp"

struct Settings {
    double aspect_ratio;
    int image_width;
    int image_height;
    int samples_per_pixel;
    int max_depth;

    hittable_list world;

    camera cam;
};

#endif