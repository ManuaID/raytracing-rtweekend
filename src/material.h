#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

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
            vec3 reflected = reflect(r.direction(), rec.normal);
            /*
                Gets the unit direction of reflect_direction within the unit circle. 
                Then add on another another vector from the point of the ray with the radius of double fuzziness
            */
            reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            //Checks if the ray is pointing within the surface or not. Moreover if it reflects or gets absord
            return (dot(scattered.direction(), rec.normal) > 0);
        };
    private:
        color albedo;
        double fuzz;
};

class dielectric : public material {
    public:
        dielectric(double refraction_index) : refraction_index(refraction_index) {}

        bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered)
        const override {
            attenuation = color(1.0, 1.0, 1.0);
            double ri = rec.front_face ? (1.0/refraction_index) : refraction_index;

            vec3 unit_direction = unit_vector(r.direction());
            double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = ri * sin_theta > 1.0;
            vec3 direction;

            if (cannot_refract || reflectance(cos_theta, ri) > random_double())
                direction = reflect(unit_direction, rec.normal);
            else
                direction = refract(unit_direction, rec.normal, ri);

            scattered = ray(rec.p, direction);
            return true;
        }

    private:
        // Refractive index in vacuum or air, or the ratio of the material's refractive index over
        // the refractive index of the enclosing media
        double refraction_index;

        static double reflectance(double cosine, double ref_index) {
            double r0 = (1 - ref_index) / (1 + ref_index);
            r0 = r0 * r0;
            return r0 + (1-r0) * pow((1 - cosine),5);
        }
};

#endif