#ifndef CAMERA_H 
#define CAMERA_H 
#include "ray.h"
#include "rtweekend.h" 

class camera {
public:
    /*camera() {
        auto aspect_ratio = 16.0 / 9.0;
        auto viewport_height = 2.0;
        auto viewport_width = aspect_ratio * viewport_height;*/
    camera(
        point3 lookfrom,
        point3 lookat,
        vec3 vup,
        double vfov, // vertical field-of-view in degrees
        double aspect_ratio,
        double aperture,
        double focus_dist,
        double _time0 = 0,
        double _time1 = 0
    ) {
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;
         w = unit_vector(lookfrom - lookat);
         u = unit_vector(cross(vup, w));
         v = cross(w, u);
        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 -
            focus_dist * w;
        lens_radius = aperture / 2;
        time0 = _time0;
        time1 = _time1;
       /*auto focal_length = 1.0;

        origin = point3(0, 0, 0);
        horizontal = vec3(viewport_width, 0.0, 0.0);
        vertical = vec3(0.0, viewport_height, 0.0);
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0,
            focal_length);*/ 
    }

    /*ray get_ray(double u, double v) const {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical -
            origin);
    }*/
    ray get_ray(double s, double t) const {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();
        return ray(
            origin + offset,
            //lower_left_corner + s * horizontal + t * vertical - origin - offset
            lower_left_corner + s * horizontal + t * vertical - origin -
            offset,
            random_double(time0, time1)
        );
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
    double time0, time1; // shutter open/close times
};
#endif