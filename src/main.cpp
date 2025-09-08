    #include "rtweekend.h"
    #include "camera.h"
    #include "hittable.h"
    #include "hittable_list.h"
    #include "sphere.h"

    // #include "raylib.h"

    int main() {

        hittable_list world;

        shared_ptr<material> ground_material = make_shared<labertian>(color(0.8,0.8,0.0));
        shared_ptr<material> mat_centre = make_shared<labertian>(color(0.1,0.2,0.5));
        shared_ptr<material> mat_left   = make_shared<dielectric>(1.50);
        shared_ptr<material> mat_right = make_shared<metal>(color(0.8,0.6,0.2),1.0);

        world.add(make_shared<sphere>(point3(0,0,-1.2), 0.5,mat_centre));
        world.add(make_shared<sphere>(point3(-1,0,-1), 0.5,mat_left));
        world.add(make_shared<sphere>(point3(1,0,-1), 0.5,mat_right));
        world.add(make_shared<sphere>(point3(0,-100.5,-1), 100,ground_material));

        camera cam;
        cam.aspect_ratio = 16.0/9.0;
        cam.image_width = 400;
        cam.pixel_sample_size = 100 ;
        cam.max_depth = 50;

        cam.render(world);
        
        std::clog << "Done.\n";
        return 0;
    }