#include "canvas.h"
#include <vector>
#include <iostream>
#include <string> 
#include <sstream>
using namespace std; 


void Canvas::writePixel(int x, int y, const Color& C) {
    int index = y * width + x; // Index to write to

    pixels[index] = C;
}

// PPM FILE 
// (IDENTIFIER)
// (WIDTH) (HEIGHT)
// (MAX COLOR VALUE)

string Canvas::convertToPpm() {
    string identifier = "P3"; 
    string widthStr = to_string(width);
    string heightStr = to_string(height); 

    return identifier + "\n" + widthStr + " " + heightStr + "\n" + "255" + "\n" + constructPixelData() + "\n";
}

std::string Canvas::constructPixelData() {
    std::ostringstream oss;

    for (int y = 0; y < height; ++y) {
        int lineLength = 0; // characters used so far on the current line

        for (int x = 0; x < width; ++x) {
            const Color& c = at(x, y);

            // Write R, G, B as separate components, each respecting 70-char rule
            auto writeComponent = [&](int value) {
                std::string s = std::to_string(value);
                int needed = (lineLength == 0 ? 0 : 1) + static_cast<int>(s.size());
                // (1 for a space if it's not the first thing on the line)

                // If this would exceed 70 chars, wrap to a new line
                if (lineLength + needed > 70) {
                    oss << "\n";
                    lineLength = 0;
                }

                // Put a space if not at the start of the line
                if (lineLength > 0) {
                    oss << " ";
                    lineLength += 1;
                }

                oss << s;
                lineLength += static_cast<int>(s.size());
            };

            writeComponent(static_cast<int>(c.r));
            writeComponent(static_cast<int>(c.g));
            writeComponent(static_cast<int>(c.b));
        }

        oss << "\n"; // end of this row of pixels
    }

    return oss.str();
}


int Canvas::getMaxColorVal() {
    int max = 0; 

    for (const Color& c : pixels) {
        if (c.r > max) max = static_cast<int>(c.r);
        if (c.g > max) max = static_cast<int>(c.g);
        if (c.b > max) max = static_cast<int>(c.b);
    }

    return max;
}