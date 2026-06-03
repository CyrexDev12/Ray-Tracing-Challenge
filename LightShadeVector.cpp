#include "LightShadeVector.h"
#include "Operations.h"


// Negate the rays direction vector, turning it around to point back at its origin. 
 void LightShadeVector::CalculateEyeVector(vector<double>& rayOrigin) {
     E = NegateTuple(rayOrigin);
 }

 // Subtract p from the position of the light source, giving you the vector poiting toward the light. 
void LightShadeVector::CalculateLightVector(vector<double> lightPosition, vector<double>& pointP) {
    L = SubtractTuples(lightPosition, pointP);
} 

void LightShadeVector::CalculateNormalVector(vector<double>& pointP, Sphere& s) {
    Matrix inverseTransform = s.getTransform().inverse();
    vector<double> objectPoint = inverseTransform.multiplyTuple(pointP);
    
    // Explicitly enforce that the normal is a VECTOR (w = 0)
    vector<double> objectNormal = SubtractTuples(objectPoint, {0, 0, 0, 1}); 
    objectNormal[3] = 0.0; 

    N = inverseTransform.transpose().multiplyTuple(objectNormal);
    N[3] = 0.0; // Ensure the output remains a clean vector
    N = NormalizeTuple(N); // Normals must be unit vectors
}

void LightShadeVector::CalculateReflectionVector() {
    // If L points from the surface toward the light: R = 2 * (N . L) * N - L
    double dotProductParam = 2 * CalculateDotProd(L, N);
    vector<double> scaledNormal = ScaleTuple(N, dotProductParam);
    
    // Correcting the subtraction order for standard ray-tracing reflection
    R = SubtractTuples(scaledNormal, L); 
    R[3] = 0.0; // Enforce vector property
}