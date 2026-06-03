#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <vector>
#include <iostream>
#include <cstdint>
using namespace std; 

struct Color {
    std::uint8_t r, g, b; 
};

bool isTuple(const vector<double> &point);
bool isPoint(const vector<double> &point);
bool isVector(const vector<double> &point);
bool TuplesEqual(const vector<double> &tup1, const vector<double> &tup2);
vector<double> AddTuples(const vector<double>& a, const vector<double>& b);
vector<double> SubtractTuples(const vector<double>& x2, const vector<double>& x1);
vector<double> NegateTuple(const vector<double>& x); 
vector<double> ScaleTuple(const vector<double>& x, double& scalar); 
double GetMagnitude(const vector<double>& x); 
void PrintTuple(const vector<double>& x); 
vector<double> NormalizeTuple(const vector<double>& x);
double CalculateDotProd(const vector<double>& x1, const vector<double>& x2);
vector<double> CrossProduct(const vector<double>& a, const vector<double>& b);
double toRadians(double degrees);

// Color 

// ============================================================================
// BASIC RGBA COLORS REFERENCE
// ============================================================================
// Format: { Red, Green, Blue, Alpha/W }
// Range:  0.0 (completely off) to 1.0 (maximum intensity)
//
// Black:   { 0.0, 0.0, 0.0, 1.0 }
// White:   { 1.0, 1.0, 1.0, 1.0 }
// Red:     { 1.0, 0.0, 0.0, 1.0 }
// Green:   { 0.0, 1.0, 0.0, 1.0 }
// Blue:    { 0.0, 0.0, 1.0, 1.0 }
// Yellow:  { 1.0, 1.0, 0.0, 1.0 }
// Cyan:    { 0.0, 1.0, 1.0, 1.0 }
// Magenta: { 1.0, 0.0, 1.0, 1.0 }
// Gray:    { 0.5, 0.5, 0.5, 1.0 }
// ============================================================================

Color makeColor(const std::vector<double>& rgb);
Color addColors(const Color& c1, const Color& c2);
Color subtractColors(const Color& c1, const Color& c2);
Color multiplyColors(const Color& c1, const Color& c2);
Color multiplyByScalar(const Color& c1, const double& scalar);
Color hadamard_product(const Color& c1, const Color& c2);
void printColor(const string& label, const Color& c);

#endif