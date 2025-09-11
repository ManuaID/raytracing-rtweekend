#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

class camera {
    public:
        double aspect_ratio = 1.0;
        int image_width = 100;
        int pixel_sample_size = 10;
        int max_depth = 10;
        /*
            Note: The parameter can be a hittable, as it is a virtual function it can be overwritten by the object within the passed in value:
            As a process it will first call the hittable_list object then the sphere object that is within the hittable_list object
        */
        void render(const hittable& world) {
            intialize();

            std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

            for(int i = 0; i < image_height; i++) {
                std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
                for(int j = 0; j < image_width; j++) {
                    color pixel_color(0,0,0);
                    for(int sample = 0; sample < pixel_sample_size; sample++) {
                        ray r = get_ray(i,j);
                        pixel_color += ray_color(r,max_depth,world);
                    }
                    write_color(std::cout, pixel_sample_scale * pixel_color);
                }
            }
        };
    private:
        int image_height;
        double pixel_sample_scale; //colour scale factor for a sample of pixel
        point3 camera_centre; //Camera Centre
        point3 pixel00_loc; //Location of pixel 0,0
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;

        void intialize() {
            pixel_sample_scale = 1.0/pixel_sample_size;

            image_height = int(image_width/aspect_ratio);
            image_height = (image_height < 1 ) ? 1: image_height;

            const double VIEWPORT_HEIGHT = 2.0;
            const double FOCAL_LENGTH = 1.0; 
            
            double viewport_width = VIEWPORT_HEIGHT * (double(image_width)/image_height);

            //Define the vector of the width and height of the view port
            vec3 viewport_u = vec3(viewport_width, 0,0);
            vec3 viewport_v = vec3(0,-VIEWPORT_HEIGHT, 0);

            //Calculate the distance between pixels
            pixel_delta_u = viewport_u/image_width;
            pixel_delta_v = viewport_v/image_height;

            //Get the left most pixel
            vec3 viewport_origin = camera_centre - vec3(0,0,FOCAL_LENGTH) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_origin + 0.5 * (pixel_delta_u + pixel_delta_v);
        };

        ray get_ray(int i , int j) const{
            vec3 offset = sample_square();
            //It calculates the centre of a pixel
            vec3 pixel_sample = pixel00_loc 
                                + ((j + offset.x()) * pixel_delta_u) 
                                + ((i + offset.y()) * pixel_delta_v);
            
            vec3 ray_origin = camera_centre;
            vec3 ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        vec3 sample_square() const{
            //Gets a random value between 0 and 1 and offset it by 0.5 which results in the range of 0.5 <= x <= 0.5
            return vec3(random_double() - 0.5, random_double() - 0.5,0);
        }

        //Return RGB value which is a point within a 3d space that corresponds to the RGB value
        color ray_color(const ray& r, int depth, const hittable& world) const{
            if(depth <= 0) {
                return color(0,0,0);
            }

            hit_record rec;
            //Sets the limit within the interval class to 0.001 to mitigate any floating point error to be confused to hit a surface at t = 0.00000000001
            if (world.hit(r,interval(0.001,infinity),rec)) {    
                ray scattered;
                color attenuation;
                if(rec.mat->scatter(r,rec,attenuation,scattered)) {
                    return attenuation * ray_color(scattered,depth - 1,world);
                }
                return color(0,0,0);
                //Creates a another sphere from point P, in the normal direction allowing. In turn allowing the ray to be amplified towards the normal.
            }

            vec3 unit_direction = unit_vector(r.direction());
            double a = 0.5 * (unit_direction.y() + 1.0);
            //Calculate blended value.
            return (1 - a) * color(1.0,1.0,1.0) + a * color(0.5, 0.7, 1.0);
        };

        
};

#endif