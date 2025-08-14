#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere: public hittable {
    public:
        sphere(const point3& c, double r, shared_ptr<material> mat): centre(c), radius(std::fmax(0,r)), mat(mat){};

        bool hit(const ray&r, interval ray_t, hit_record& rec) const override{
            vec3 OC = centre - r.origin();
            double a = r.direction().length_squared();
            double h = dot(r.direction(),OC);
            double c = OC.length_squared() - radius*radius;

            double discriminant = h*h - a*c;

            if(discriminant < 0 ) {
                return false;
            }

            double sqrtd = std::sqrt(discriminant);
            double root = (h - sqrtd)/a;

            //Checking if the ray is within the circle additionally has 2 intersect
            if(!ray_t.surrounds(root)) {
                root = (h + sqrtd)/a;
                if (!ray_t.surrounds(root)) {
                    return false;
                }
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - centre)/radius;
            rec.set_face_normal(r,outward_normal);
            rec.mat = mat;

            return true;
        }

    private:
        point3 centre;
        double radius;
        shared_ptr<material> mat;
};

#endif