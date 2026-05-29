#include "Ray.h"


// Compute the point at the given distance t along the ray
  vector<double> Ray::position(double t) {
    vector<double> scaledDirection = ScaleTuple(direction, t);
    return AddTuples(origin, scaledDirection);
}