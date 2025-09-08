#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.h"

class interval {
    public:
        double min, max;

        interval(): min(-infinity), max(+infinity) {}
        interval(const double& tmin, const double& tmax): min(tmin), max(tmax){};

        double size() {
            return max - min;
        }

        bool compare(double x) {
            return min <= x && x <= max;
        }

        bool surrounds(double x) {
            return min < x && x < max;
        }

        double clamp(double x) const {
            if (x < min) return min;
            if (x > max) return max;
            return x;
        }

        //Creates 2 static object referencing interval named empty and universal
        static const interval empty, universal;
    };

/*
    Simple visualization:
    [-infinity               0               +infinity]
    empty is basically drawing a line from +infinity to - infinity basically everything else which is empty
    universal is whatever the opposite of empty is, which is every value
*/
const interval interval::empty = interval(+infinity, - infinity);
const interval interval::universal = interval(-infinity, +infinity);

#endif