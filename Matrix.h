#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
using namespace std; 

// Using 2D vectors to represent matricies 
// This class includes all of the operations required for matricies in a ray tracing engine 
// Author: Luke Neumann 

class Matrix {
    private:

    int rows; 
    int cols; 
    vector<vector<double>> matrix; 

    public:

    // Constructors
    Matrix(int r, int c, vector<double>& arr); 
    Matrix(int r, int c, vector<vector<double>>& m);

    // Getters 

    int getRows() {
        return rows; 
    }

    int getCols() {
        return cols; 
    }


    // Operations 
    
    Matrix multiplyMatrix(Matrix& b);
    Matrix transpose();
    Matrix inverse();
    Matrix cofactorMatrix();
    Matrix scalarMultiply(double& scalar);
    double determinant(); 
    double determinantHelper(vector<vector<double>> mat);
    double minorDeterminant(int skipRow, int skipCol);
    
    
    // Debug Functions 

    void printMatrix();

};











#endif