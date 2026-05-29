#include "Ray.h"


// Compute the point at the given distance t along the ray
  vector<double> Ray::position(double t) {
    vector<double> scaledDirection = ScaleTuple(direction, t);
    return AddTuples(origin, scaledDirection);
}


Ray Ray::transform(Matrix m) {
    Ray transformedRay;

    transformedRay.origin = m.multiplyTuple(origin);
    transformedRay.direction = m.multiplyTuple(direction);

    return transformedRay;
}