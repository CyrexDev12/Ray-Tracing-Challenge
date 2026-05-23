#include <iostream>
#include <vector> 
#include <cmath>
#include <limits> 
#include <algorithm>
#include <stdexcept>   // for std::invalid_argument
#include "Operations.h"
#include <cstdint>
using namespace std; 

// Tunables 
constexpr double kabsTol  = 1e-9;  // Absolute tolerance for a very small magnitude 
constexpr double KrelTol  = 1e-8;  // Relative tolerance scales with value
constexpr double kTEps    = 1e-7;  // "hit" distance threshold (t > kTEps)
constexpr double kRayBias = 1e-4;  // Ray origin offset factor 

inline bool nearlyEqual(double a, double b,
                        double relTol = KrelTol,
                        double absTol = kabsTol) {
    if (a == b) return true; // Handles infinities and exact matches 

    // If either is not finite, treat as not nearly equal
    if (!isfinite(a) || !isfinite(b)) {
        return false;
    }

    const double diff  = fabs(a - b);
    const double scale = max(fabs(a), fabs(b));

    return diff <= max(absTol, relTol * scale);
}

// ----------------------------------------------------------------------------- //
// Tuple = (x, y, z, w)
// A tuple with w == 1 is a point, and a tuple with w == 0 is a vector 
// ----------------------------------------------------------------------------- //

// Matches: bool isTuple(const vector<double> &point);
bool isTuple(const vector<double> &point) {
    // For this assignment, let's define a "tuple" as a 4D (x,y,z,w) vector.
    return point.size() == 4;
}

// Matches: vector<double> SubtractTuples(const vector<double>& x2, const vector<double>& x1);
vector<double> SubtractTuples(const vector<double>& x2, const vector<double>& x1) {
    if (x2.size() != x1.size()) {
        throw invalid_argument("SubtractTuples: vectors must have same size");
    }

    vector<double> result;
    result.reserve(x1.size());

    for (size_t i = 0; i < x1.size(); ++i) {
        result.push_back(x2[i] - x1[i]);
    }

    return result;
}

// Matches: vector<double> NegateTuple(const vector<double>& x);
vector<double> NegateTuple(const vector<double>& x) {
    vector<double> result;
    result.reserve(x.size());

    for (double v : x) {
        result.push_back(-v);   // 0 - v
    }

    return result;
}

// Matches: vector<double> ScaleTuple(const vector<double>& x, double& scalar);
vector<double> ScaleTuple(const vector<double>& x, double& scalar) {
    vector<double> result;
    result.reserve(x.size());

    for (size_t i = 0; i < x.size(); ++i) {
        result.push_back(x[i] * scalar);
    }

    return result; 
}

// Matches: double GetMagnitude(const vector<double>& x);
double GetMagnitude(const vector<double>& x) {
    double sum = 0.0;

    for (size_t i = 0; i < x.size(); ++i) {
        sum += x[i] * x[i];
    }

    return sqrt(sum);
}

// Matches: void PrintTuple(const vector<double>& x);
void PrintTuple(const vector<double>& x) {
    cout << "{";
    for (size_t i = 0; i < x.size(); ++i) {
        cout << x[i];
        if (i + 1 < x.size()) {
            cout << ", ";
        }
    }
    cout << "}\n";
}

vector<double> NormalizeTuple(const vector<double>& x) {
    double mag = GetMagnitude(x);

    // Guard against zero vector (can't normalize it)
    if (nearlyEqual(mag, 0.0)) {
        throw invalid_argument("NormalizeTuple: cannot normalize zero-length vector");
    }

    double invMag = 1.0 / mag;

    vector<double> result;
    result.reserve(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        result.push_back(x[i] * invMag);
    }

    return result;
}

// Matches: bool TuplesEqual(const vector<double> &tup1, const vector<double> &tup2);
bool TuplesEqual(const vector<double> &tup1, const vector<double> &tup2) {
    if (tup1.size() != tup2.size()) return false;

    for (size_t i = 0; i < tup1.size(); ++i) {
        if (!nearlyEqual(tup1[i], tup2[i])) {
            return false; 
        }
    }
    return true;
}

double CalculateDotProd(const vector<double>& x1, const vector<double>& x2) {
    if (x1.size() != x2.size()) {
        throw std::invalid_argument("Vectors must be the same length for dot product.");
    }

    double sum = 0.0;
    for (size_t i = 0; i < x1.size(); ++i) {
        sum += x1[i] * x2[i];
    }
    return sum;
}


vector<double> CrossProduct(const vector<double>& a, const vector<double>& b) {
    if (a.size() != 3 || b.size() != 3) {
        throw invalid_argument("CrossProduct requires 3D vectors.");
    }

    if (isTuple(a) || isTuple(b)) {
        throw invalid_argument("Cross product cannot be computed with tuples!");
    }

    return {
        a[1] * b[2] - a[2] * b[1],  // x component
        a[2] * b[0] - a[0] * b[2],  // y component
        a[0] * b[1] - a[1] * b[0]   // z component
    };
}

Color makeColor(const std::vector<double>& rgb) {
    Color c{0, 0, 0}; // default black if input is bad

    if (rgb.size() < 3) {
        std::cerr << "makeColor: rgb vector has fewer than 3 components\n";
        return c;
    }

    auto toByte = [](double v) -> std::uint8_t {
        // If it's in 0–1 range, assume normalized and scale
        if (v >= 0.0 && v <= 1.0) {
            v *= 255.0;
        }

        // Clamp to 0–255
        if (v < 0.0) v = 0.0;
        if (v > 255.0) v = 255.0;

        return static_cast<std::uint8_t>(std::round(v));
    };

    c.r = toByte(rgb[0]);
    c.g = toByte(rgb[1]);
    c.b = toByte(rgb[2]);

    return c;
}


Color addColors(const Color& c1, const Color& c2) {
    Color newColor{0, 0, 0};

    auto addChannel = [](std::uint8_t a, std::uint8_t b) -> std::uint8_t {
        int sum = static_cast<int>(a) + static_cast<int>(b);
        if (sum > 255) sum = 255;      // clamp at max
        return static_cast<std::uint8_t>(sum);
    };

    newColor.r = addChannel(c1.r, c2.r);
    newColor.g = addChannel(c1.g, c2.g);
    newColor.b = addChannel(c1.b, c2.b);

    return newColor;
}

Color subtractColors(const Color& c1, const Color& c2) {
    Color newColor{0, 0, 0};

    auto subChannel = [](std::uint8_t a, std::uint8_t b) -> std::uint8_t {
        int diff = static_cast<int>(a) - static_cast<int>(b);
        if (diff < 0) diff = 0;      // clamp at 0
        return static_cast<std::uint8_t>(diff);
    };

    newColor.r = subChannel(c1.r, c2.r);
    newColor.g = subChannel(c1.g, c2.g);
    newColor.b = subChannel(c1.b, c2.b);

    return newColor;
}

Color multiplyColors(const Color& c1, const Color& c2) {
    Color newColor{0, 0, 0};

    auto mulChannel = [](std::uint8_t a, std::uint8_t b) -> std::uint8_t {
        int prod = static_cast<int>(a) * static_cast<int>(b);
        if (prod > 255) prod = 255;
        return static_cast<std::uint8_t>(prod);
    };

    newColor.r = mulChannel(c1.r, c2.r);
    newColor.g = mulChannel(c1.g, c2.g);
    newColor.b = mulChannel(c1.b, c2.b);

    return newColor;
}

Color multiplyByScalar(const Color& c1, const double& scalar) {
    Color newColor{0, 0, 0};

    auto scaleChannel = [&](std::uint8_t v) -> std::uint8_t {
        double scaled = static_cast<double>(v) * scalar;

        // Clamp to [0, 255]
        if (scaled < 0.0)   scaled = 0.0;
        if (scaled > 255.0) scaled = 255.0;

        return static_cast<std::uint8_t>(std::round(scaled));
    };

    newColor.r = scaleChannel(c1.r);
    newColor.g = scaleChannel(c1.g);
    newColor.b = scaleChannel(c1.b);

    return newColor;
}


Color hadamard_product(const Color& c1, const Color& c2) {
    return multiplyColors(c1, c2);
}

void printColor(const string& label, const Color& c) {
    cout << label << " = ("
         << static_cast<int>(c.r) << ", "
         << static_cast<int>(c.g) << ", "
         << static_cast<int>(c.b) << ")\n";
}

double toRadians(double degrees) {
    return degrees * (M_PI / 180.0);
}