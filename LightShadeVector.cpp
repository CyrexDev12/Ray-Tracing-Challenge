#include "LightShadeVector.h"
#include "Operations.h"


// Negate the rays direction vector, turning it around to point back at its origin. 
 void LightShadeVector::CalculateEyeVector(vector<double>& rayOrigin) {
     E = NegateTuple(rayOrigin);
 }

 // Subtract p from the position of the light source, giving you the vector poiting toward the light. 
void LightShadeVector::CalculateLightVector(vector<double>& lightPosition, vector<double>& pointP) {
    L = SubtractTuples(lightPosition, pointP);
} 

void LightShadeVector::CalculateNormalVector(vector<double>& pointP, Sphere& s) {
    // To calculate the normal vector, we need to find the point on the sphere's surface that corresponds to pointP. 
    // We can do this by applying the inverse of the sphere's transformation to pointP, which will give us the point in object space. 
    // Then we can calculate the normal vector in object space, which is simply the vector from the center of the sphere to the point on its surface. 
    // Finally, we can apply the transpose of the inverse of the sphere's transformation to the normal vector to get it back into world space. 

    Matrix inverseTransform = s.getTransform().inverse();
    vector<double> objectPoint = inverseTransform.multiplyTuple(pointP);
    vector<double> objectNormal = SubtractTuples(objectPoint, {0, 0, 0}); // Center of sphere is at origin in object space
    N = inverseTransform.transpose().multiplyTuple(objectNormal);
}


void LightShadeVector::CalculateReflectionVector(vector<double>& L, vector<double>& N) {
    // The reflection vector R can be calculated using the formula: R = L - 2 * (L . N) * N
    double dotProductParam = 2 * CalculateDotProd(L, N);
    vector<double> scaledNormal = ScaleTuple(N, dotProductParam);
    R = SubtractTuples(L, scaledNormal);
}