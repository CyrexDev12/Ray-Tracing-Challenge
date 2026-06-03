#ifndef LIGHTING_H
#define LIGHTING_H
#include "LightShadeVector.h"
#include "PointLight.h"
#include "Operations.h"
#include "Material.h"

class Lighting { 
    private: 
    LightShadeVector lightShadeVecs; 
    PointLight pointLight; 
    Color color; 

    public: 

    // Constructor 
    Lighting(LightShadeVector lsv, PointLight ptLight);


    void ProcessLighting(Material mat, vector<double>& point); 






};








#endif