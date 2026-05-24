#include <iostream>
using namespace std; 
//#include "Operations.h"
//#include "BasicPhysics.h"
#include <vector>
// #include "canvas.h"
#include <string> 
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Matrix.h"


const double PI = 3.14159265358979323846;


// int main() {
//     Matrix transform;
//     transform = transform.rotateX(M_PI / 2);

//     vector<double> p = {0, 1, 0, 1};

//     vector<double> result = transform.multiplyTuple(p);

//     for (int i = 0; i < result.size(); i++) {
//         cout << result[i] << " ";
//     }

//     return 0;

// }

// TESTS 



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
} */



using namespace std;

bool almostEqual(double a, double b) {
    return fabs(a - b) < 0.00001;
}

bool tupleEqual(const vector<double>& a, const vector<double>& b) {
    if (a.size() != b.size()) return false;

    for (int i = 0; i < a.size(); i++) {
        if (!almostEqual(a[i], b[i])) return false;
    }

    return true;
}

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

int main() {
    Matrix transform;
    vector<double> p = {2, 3, 4, 1};

    runShearingTest(
        "x moves in proportion to y",
        transform.shearing(1, 0, 0, 0, 0, 0),
        p,
        {5, 3, 4, 1}
    );

    runShearingTest(
        "x moves in proportion to z",
        transform.shearing(0, 1, 0, 0, 0, 0),
        p,
        {6, 3, 4, 1}
    );

    runShearingTest(
        "y moves in proportion to x",
        transform.shearing(0, 0, 1, 0, 0, 0),
        p,
        {2, 5, 4, 1}
    );

    runShearingTest(
        "y moves in proportion to z",
        transform.shearing(0, 0, 0, 1, 0, 0),
        p,
        {2, 7, 4, 1}
    );

    runShearingTest(
        "z moves in proportion to x",
        transform.shearing(0, 0, 0, 0, 1, 0),
        p,
        {2, 3, 6, 1}
    );

    runShearingTest(
        "z moves in proportion to y",
        transform.shearing(0, 0, 0, 0, 0, 1),
        p,
        {2, 3, 7, 1}
    );

    return 0;
}