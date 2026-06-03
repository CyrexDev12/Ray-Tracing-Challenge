#include "PointLight.h"

// Constructor for PointLight, initializes position and intensity
// Default color white: rgb(255, 255, 255) 
  PointLight::PointLight(vector<double> pos, Color c, double ins) {
    if (!isPoint(pos)) {
        throw invalid_argument("Must be a point tuple!");
    }

    color = c; 
    Intensity = ins; 
  }


