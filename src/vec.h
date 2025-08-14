#ifndef VEC_H
#define VEC_H

class vec3{
    public:
        /*
            3 values for location, offset, colour, directions
            Location: x,y,z
            colour: r,g,b
            so on...
        */ 
        double e[3]; 

        //Constructor intializing e to (0,0,0)
        vec3(): e{0,0,0} {};

        vec3(double e1, double e2, double e3): e{e1,e2,e3} {};

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        //Returns a negative value of the 3 values in a array by overriding negative(-) sign
        vec3 operator-() const { return vec3(-e[0],-e[1],e[2]);}
        //When trying to access the value it returns the actual value at that index a pointer to the class
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        //It takes another vec3 object and add it to the current existing vec3 object and returns a pointer
        vec3& operator+=(const vec3& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            
            return *this;
        }

        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;

            return *this;
        }

        // Gets the reference to the object and use the *= operator and multiply it by 1/t
        vec3& operator/=(double t) {
            return *this *= 1/t;
        }

        //It's calculating the magnitude of the vector from the origin to the point
        double length() const {
            return std::sqrt(length_squared());
        }

        double length_squared() const{
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        static vec3 random(double min, double max) {
            return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
        }

};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << '\n';
}

inline vec3 operator+(const vec3& u,const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

inline bool operator<(const vec3& u, const vec3& v) {
    return (std::fabs(u.e[0]) < std::fabs(v.e[0]) && std::fabs(u.e[1]) < std::fabs(v.e[1]) && std::fabs(u.e[2]) < std::fabs(v.e[2]));
}

inline bool operator<(const vec3& u, double t) {
    return (std::fabs(u.e[0]) < t && std::fabs(u.e[1]) < t && std::fabs(u.e[2]) < t);
}

inline bool operator<(double t, const vec3& v) {
    return (t < v);
}

//Find the dot product between 2 vector points
inline double dot(const vec3& u, const vec3 & v) {
    return u.e[0] * v.e[0] 
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

//Find the the cross product between the 2 vector points
inline vec3 cross(const vec3& u, const vec3 & v) {
    return vec3(
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]
    );
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline vec3 random_unit_vector() {

    /*
        Generates random vector that originates from the point in which the ray hit. 
        Then filtering out some vector to cotain only a vector that has a length less than the unit circle radius of 1.
        If it finds a vector that fits the condition it will normalize it
    */
    while(true) {
        vec3 p = vec3::random(-1,1);
        double lensq = p.length_squared();

        //It checks for bogus vector
        if(1e-160 < lensq && lensq <= 1.0) {
            return p / sqrt(lensq);
        }
    }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 temp_vec = random_unit_vector();

    if(dot(temp_vec, normal) > 0.0) {
        return temp_vec;
    }
    else {
        return -temp_vec;
    }
}

inline vec3 reflect_value(const vec3& u, const vec3& normal) {
    return u - 2*(dot(u,normal)) * normal;
}

#endif