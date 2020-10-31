#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "indicators.hpp"
#include "json.hpp"

#include "main.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "material.hpp"
#include "json_reader.hpp"

color ray_color(const ray &r, const hittable &world, int depth)
{
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
    {
        return color(0, 0, 0);
    }

    if (world.hit(r, 0.0001, infinity, rec))
    {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0, 0, 0);
    }

    // Sky
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); // Lerp
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        Settings settings = read_json(argv[1]);
        // Progress Bar Setup

        std::ofstream output_file;
        output_file.open(argv[2]);

        using namespace indicators;

        // Hide cursor
        show_console_cursor(false);
        std::cout << "\n";
        indicators::ProgressBar bar{
            option::BarWidth{30},
            option::Start{" ["},
            option::Fill{"█"},
            option::Lead{"█"},
            option::Remainder{"-"},
            option::End{"]"},
            option::PrefixText{"Raytracing Image"},
            option::ShowPercentage{true},
            option::ForegroundColor{Color::cyan},
            option::ShowElapsedTime{true},
            option::ShowRemainingTime{true},
            option::MaxProgress{settings.image_height},
            option::FontStyles{
                std::vector<FontStyle>{FontStyle::bold}}};

        // Render

        output_file << "P3\n"
                    << settings.image_width << " " << settings.image_height << "\n255\n";

        for (int j = settings.image_height - 1; j >= 0; --j)
        { // for each row (starting at the bottom row)
            for (int i = 0; i < settings.image_width; ++i)
            { // for each column (starting at the left most column)
                color pixel_color(0, 0, 0);
                for (int s = 0; s < settings.samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (settings.image_width - 1);
                    auto v = (j + random_double()) / (settings.image_height - 1);
                    ray r = settings.cam.get_ray(u, v);
                    pixel_color += ray_color(r, settings.world, settings.max_depth); // Sum all the samples
                }
                write_color(output_file, pixel_color, settings.samples_per_pixel);
            }
            bar.tick();
        }

        output_file.close();
        show_console_cursor(true);
    }
    else
    {
        std::cout << "Usage: \n"
                  << "./<exe> <json_input> <file_output>";
    }

    return 0;
}
