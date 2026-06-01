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


public:
// Default constructor 
Sphere(); 


 

vector<double> intersect(Ray ray);

};

#endif