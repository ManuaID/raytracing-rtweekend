#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "rtweekend.h"

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const {
            return false;
        };
};


class labertian: public material {
    public:
        labertian(const color& albedo): albedo(albedo){};

        bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const override {
            vec3 scatter_direction = rec.normal + random_unit_vector();

            if(scatter_direction < 0) {
                scatter_direction = rec.normal;
            }
            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }
    private:
        //Latin word that stands for whiteness
        color albedo;
};

class metal: public material{
    public:
        metal(const color& albedo, double fuzziness): albedo(albedo), fuzz(fuzziness < 1 ? fuzziness:1){};

        bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const {
            vec3 reflect_direction = reflect_value(r.direction(), rec.normal);
            /*
                Gets the unit direction of reflect_direction within the unit circle. 
                Then add on another another vector from the point of the ray with the radius of double fuzziness
            */
            vec3 reflected = unit_vector(reflect_direction) + fuzz * random_unit_vector();
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            //Checks if the ray is pointing within the surface or not. Moreover if it reflects or gets absord
            return (dot(scattered.direction(), rec.normal) > 0);
        };
    private:
        color albedo;
        double fuzz;
};

#endif