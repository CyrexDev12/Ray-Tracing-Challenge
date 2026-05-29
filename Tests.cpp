#include "Tests.h"
#define M_PI       3.14159265358979323846   // pi
#include <cmath>
#include <fstream>
using namespace std; 


// Another helper function
bool almostEqual(double a, double b) {
    return fabs(a - b) < 0.00001;
}

// Helper Function 
bool tupleEqual(const vector<double>& a, const vector<double>& b) {
    if (a.size() != b.size()) return false;

    for (int i = 0; i < a.size(); i++) {
        if (!almostEqual(a[i], b[i])) return false;
    }

    return true;
}


// SHEARING TRANSFORMATION TEST 
// Status: Test passeed 
void runShearingTest(string testName, Matrix transform, vector<double> p, vector<double> expected) {
    vector<double> result = transform.multiplyTuple(p);

    cout << testName << ": ";

    if (tupleEqual(result, expected)) {
        cout << "PASS";
    } else {
        cout << "FAIL - got ";
        for (double value : result) {
            cout << value << " ";
        }
    }

    cout << endl;
}

// Write projectile Motion Test 
// Status: Passed 
/* void ppmTest() {
    vector<double> initPos = {0.0, 0.0};    // meters (or units)
    vector<double> velocity = {8.0, 15.0};  // initial v (vx, vy)

    double gravity = -9.8;   // downward
    double wind    = 0.0;    // no horizontal accel
    double dt      = 0.05;   // smaller dt → smoother arc

    Projectile myProj(initPos, velocity, gravity, wind, dt);

    Canvas myCanvas(800, 300);   // wider than tall

    // red color
    vector<double> redColVec = {255, 100, 100};
    Color Red = makeColor(redColVec);

    // map physics units → pixels
    const double scaleX = 10.0;  // 1 unit = 10 pixels horizontally
    const double scaleY = 10.0;  // 1 unit = 10 pixels vertically

    vector<double> currPos = initPos;

    while (currPos[1] >= 0.0) {  // stop when projectile hits the "ground"
        // world → canvas coords
        int canvasX = static_cast<int>(currPos[0] * scaleX);
        int canvasY = myCanvas.height - 1 - static_cast<int>(currPos[1] * scaleY);

        if (canvasX >= 0 && canvasX < myCanvas.width &&
            canvasY >= 0 && canvasY < myCanvas.height) {
            myCanvas.writePixel(canvasX, canvasY, Red);
        }

        currPos = myProj.Tick();
    }

    // write out PPM
    std::string ppm = myCanvas.convertToPpm();
    std::ofstream out("projectile.ppm");
    out << ppm;
    out.close();
} 
*/

// Chaining Matrix Translation Test 
// Status Passed 
void chainingMatrixTransTest() {
    Matrix transform;

Matrix A = transform.rotateX(M_PI / 2);
Matrix B = transform.scale(5, 5, 5);
Matrix C = transform.translation(10, 5, 7);

// Chain: C * B * A
Matrix chain = C.multiplyMatrix(B).multiplyMatrix(A);

vector<double> p = {1, 0, 1, 1};

vector<double> result = chain.multiplyTuple(p);

for (double val : result) {
    cout << round(val * 100000) / 100000 << " ";
}

}


// Represent points as homogeneous coordinates: (x, y, z, w)
// The clock lies flat in the XY plane, so z = 0.
// To spin points around the center of the clock, rotate around the Z axis.
// For Every Hour 
// Matrix rotation = Matrix::rotateZ(angle * hour);
// vector<double> rotated = rotation.multiplyTuple(point);
// Then we convert from math coordinates to canvas pixels 
// int x = canvasWidth / 2 + rotated[0] * radius;
// int y = canvasHeight / 2 + rotated[1] * radius;

// White rgb(255, 255, 255)
void AnalogClockPPM() {
    Canvas canvas(500, 500);

    vector<double> whiteColorVec = {255, 255, 255};
    Color white = makeColor(whiteColorVec);

    double radius = 200.0;
    double angleStep = M_PI / 6.0;

    vector<double> pt = {0, -1, 0, 1};

    for (int hour = 0; hour < 12; hour++) {
        Matrix transform;
        Matrix rm = transform.rotateZ(angleStep * hour);

        vector<double> rotated = rm.multiplyTuple(pt);

        int x = static_cast<int>(canvas.width / 2 + rotated[0] * radius);
        int y = static_cast<int>(canvas.height / 2 + rotated[1] * radius);

        canvas.writePixel(x, y, white);
    }

    ofstream out("analogClock.ppm");

    if (!out) {
        cerr << "Could not create analogClock.ppm" << endl;
        return;
    }

    out << canvas.convertToPpm();
}