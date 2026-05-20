#include <iostream>
using namespace std; 
#include "Operations.h"
#include "BasicPhysics.h"
#include <vector>
#include "canvas.h"
#include <string> 
#include <sstream>
#include <iostream>
#include <fstream>

int main() {
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

    return 0;
}