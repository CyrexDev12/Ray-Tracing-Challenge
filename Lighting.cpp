#include "Lighting.h"
#include <cmath>


/*
Color Sphere::lighting(vector<double>& point, PointLight ptLight, LightShadeVector lsv) {
    
    // Combine the surface color with the light's color/intensity 
    Color effectiveColor = multiplyColors(material.color, ptLight.getIntensity()); 

    // Find the direction to the light source 
    lsv.CalculateLightVector(ptLight.getPosition(), point);

    // Compute the ambient contribution 
    Color ambient = multiplyByScalar(effectiveColor, material.ambient);

    // LightDotNorm represents the cosine of the angle between the light vector and the normal vector.
    // A negative number means the light is on the other side of the surface. 
    double lightDotNorm = CalculateDotProd(lsv.L, lsv.N); 
        if (lightDotNorm < 0) {
            material.diffuse = 0; // Set to black 
            material.specular = 0; 
        } else {
            // Compute the diffuse contribution 
            Color diffuse =  multiplyByScalar(multiplyByScalar(effectiveColor, material.diffuse), lightDotNorm);

            // ReflectDotEye represents the cosine of the angle between the reflection vector and the eye vector. 
            // A negative number means the light reflects away from the eye. 
           lsv.CalculateReflectionVector();


        }



}

*/ 

    //TODO: Color struct for ambient, diffuse, specular? 

    void Lighting::ProcessLighting(Material mat, vector<double>& point) {

        // Combine the surface color with the light's color/intensity 
        Color effectiveColor = multiplyByScalar(mat.color, pointLight.getIntensity());

         // Find the direction to the light source 
         lightShadeVecs.CalculateLightVector(pointLight.getPosition(), point);

          // Compute the ambient contribution 
        Color ambient = multiplyByScalar(effectiveColor, mat.ambient);

        double lightDotNorm = CalculateDotProd(lightShadeVecs.L, lightShadeVecs.N); 
        if (lightDotNorm < 0) {
            mat.diffuse = 0; // Set to black 
            mat.specular = 0; 
        } else {
            // Compute the diffuse contribution 
             Color diffuse =  multiplyByScalar(multiplyByScalar(effectiveColor, mat.diffuse), lightDotNorm);

            // ReflectDotEye represents the cosine of the angle between the reflection vector and the eye vector. 
            // A negative number means the light reflects away from the eye. 
           lightShadeVecs.CalculateReflectionVector();
           double reflectDotProd = CalculateDotProd(lightShadeVecs.R, lightShadeVecs.E); 

           if (reflectDotProd <= 0) {
            mat.specular = 0; // Set to black 
           } else {
                // Compute the specular contribution 
                double factor = pow(reflectDotProd, mat.shininess);
                mat.specular = pointLight.getIntensity() * mat.specular * factor; 
           }

        }

        
    }