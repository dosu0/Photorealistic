#ifndef JSON_READER_HPP
#define JSON_READER_HPP

#include "json.hpp"

#include "settings.hpp"
#include "main.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "material.hpp"


Settings read_json(const char* file_path)
{
    using namespace nlohmann;

    Settings settings;
    //Json Input Stuff
    std::ifstream json_file;

    json_file.open(file_path);

    json parsed_json = json::parse(json_file);

    json_file.close();
    //End of Json input stuff

    std::ofstream output_file;
    std::string output_file_name = static_cast<std::string>(parsed_json["image"]["output_file_name"]);

    // Image
    const int aspect_ratio_0 = static_cast<int>(parsed_json["image"]["aspect_ratio"][0]);
    const int aspect_ratio_1 = static_cast<int>(parsed_json["image"]["aspect_ratio"][1]);
    settings.aspect_ratio = aspect_ratio_0 / aspect_ratio_1;

    settings.image_width = static_cast<int>(parsed_json["image"]["image_width"]);
    settings.image_height = static_cast<int>(settings.image_width / settings.aspect_ratio);
    settings.samples_per_pixel = static_cast<int>(parsed_json["image"]["samples"]); // Anti aliasing
    settings.max_depth = static_cast<int>(parsed_json["image"]["max_depth"]);

    // World

    for (auto surface : parsed_json["surfaces"])
    {
        if (surface["shape"] == "sphere")
        {
            auto json_material = surface["material"];
            shared_ptr<material> sphere_material;

            if (json_material["type"] != NULL)
            {
                if (json_material["type"] == "lambertian")
                {
                    if (json_material["color"] != NULL)
                    {
                        color albedo(
                            static_cast<double>(json_material["albedo"][0]),
                            static_cast<double>(json_material["albedo"][1]),
                            static_cast<double>(json_material["albedo"][2]));
                        sphere_material = make_shared<lambertian>(albedo);
                    }
                }

                else if (json_material["type"] == "metal")
                {
                    color albedo(
                        static_cast<double>(json_material["albedo"][0]),
                        static_cast<double>(json_material["albedo"][1]),
                        static_cast<double>(json_material["albedo"][2]));

                    double fuzz = static_cast<double>(json_material["fuzz"]);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                }

                else if (json_material["type"] == "dielectric")
                {
                    double ri = static_cast<double>(json_material["ri"]);
                    sphere_material = make_shared<dielectric>(ri);
                }
                // End of Matierial Set
            }

            point3 pos(
                surface["posistion"][0],
                surface["posistion"][1],
                surface["posistion"][2]);

            double radius = static_cast<double>(surface["radius"]);
            settings.world.add(make_shared<sphere>(pos, radius, sphere_material));
        }
    }

    // Camera

    point3 look_from(
        static_cast<int>(parsed_json["camera"]["look_from"][0]),
        static_cast<int>(parsed_json["camera"]["look_from"][1]),
        static_cast<int>(parsed_json["camera"]["look_from"][2]));

    point3 look_at(
        static_cast<int>(parsed_json["camera"]["look_at"][0]),
        static_cast<int>(parsed_json["camera"]["look_at"][1]),
        static_cast<int>(parsed_json["camera"]["look_at"][2]));

    point3 vup(
        static_cast<double>(parsed_json["camera"]["vup"][0]),
        static_cast<double>(parsed_json["camera"]["vup"][1]),
        static_cast<double>(parsed_json["camera"]["vup"][2]));

    int v_fov = static_cast<int>(parsed_json["camera"]["v_fov"]);

    double dist_to_focus;
    if (parsed_json["camera"]["auto_focus"])
    {
        dist_to_focus = (look_from - look_at).length();
    }
    else
    {
        dist_to_focus = static_cast<double>(parsed_json["camera"]["dist_to_focus"]);
    }

    double aperture = static_cast<double>(parsed_json["camera"]["aperture"]);

    settings.cam = camera(look_from, look_at, vup, v_fov, settings.aspect_ratio, aperture, dist_to_focus);

    return settings;
}
#endif