#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <vector> 
#include "Ray.h"
using namespace std; 



class Sphere {

private: 
double radius; 
double diamater;
vector<double> position;
Matrix transformMatrix; // Transformation matrix for the sphere (e.g., for scaling, translation, etc.)


public:
// Default constructor 
Sphere(); 


 

vector<double> intersect(Ray ray);

Matrix getTransform() {
    return transformMatrix;

}


void settransform(Matrix m) {
    this->transformMatrix = m;

} 




};


#endif