#include "Sphere.h"
#include <cmath>


// Default constructor
Sphere::Sphere() {
    radius = 1.0;
    diamater = 2.0;
    position = {0.0, 0.0, 0.0}; // Center of the sphere at the origin
}

// Return t values of the interesection points 
vector<double> Sphere::intersect(Ray ray) {
    vector<double> intersections;
    // Compute the vector from the ray origin to the sphere center
    vector<double> oc = {ray.origin[0] - position[0], ray.origin[1] - position[1], ray.origin[2] - position[2]};


    // Coefficients for the quadratic equation
    double a = ray.direction[0] * ray.direction[0] + ray.direction[1] * ray.direction[1] + ray.direction[2] * ray.direction[2];
    double b = 2.0 * (oc[0] * ray.direction[0] + oc[1] * ray.direction[1] + oc[2] * ray.direction[2]);
    double c = oc[0] * oc[0] + oc[1] * oc[1] + oc[2] * oc[2] - radius * radius;

    // Compute the discriminant
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        // No intersection
        return intersections;
    } else {
        // Compute the two intersection points
        double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
        double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
        intersections.push_back(t1);
        intersections.push_back(t2);
        return intersections;
    }

   
}