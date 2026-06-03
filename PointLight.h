#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include <iostream>
#include <vector>
#include "Operations.h"
using namespace std;


// No size or shape, exists at a single point in space, defined by intensity (how bright it is), the intensity also describes the light source.



class PointLight {
    private:
    vector<double> position; // PointLight's position in space
    Color color; // The color and brightness of the light
    double Intensity; // The value of intesnity 0-1 


    public: 
    PointLight(vector<double> pos, Color c, double ins);


    Color getColor() {
        return color; 
    }


    double getIntensity() {
        return Intensity; 
    }



    vector<double> getPosition() {
        return position; 
    }

    void setPosition(vector<double> newPosition) {
        if (!isPoint(newPosition)) {
            throw invalid_argument("PointLight position must be a point (w = 1)");
        }
        position = newPosition;
    }


};







#endif