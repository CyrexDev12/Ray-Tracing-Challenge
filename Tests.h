#ifndef TESTS_H
#define TESTS_H
#include <iostream>
#include "Matrix.h"
#include "Operations.h"
#include "BasicPhysics.h"
#include "canvas.h"
#include "Ray.h"
// Testing header file
// Includes all the methods to test our implementations 



void runShearingTest(string testName, Matrix transform, vector<double> p, vector<double> expected);
void chainingMatrixTransTest();
void AnalogClockPPM();

void runRayTransformTests();




#endif