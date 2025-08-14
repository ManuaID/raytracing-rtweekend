#ifndef HITTABLE_H
#define HITTABLE_H

class material;

struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    shared_ptr<material> mat;

    //TODO: Understand the math behind these functions further
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {

        //set the hit record normal
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face? outward_normal: -outward_normal;
    }
};

class hittable {
    //Compiler generates the deconstructor without any custom logic
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r, interval ray_t ,hit_record& rec) const = 0;
};

#endif