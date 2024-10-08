#include "space.hpp"
#include "body.hpp"
#include <iostream>

int main() {
    // Create Spcae object
    Space space(Coor(1, 1, 1));

    // Initalize Space
    space.setScreen(Coor2d(100, 100));
    space.setCamera(20, 10, 50);  // Camera(depth, minDepth, maxDepth)

    // Create cube
    Coor st(0, 0, 0);
    Coor v0(1, 0, 0);
    Coor v1(0, 1, 0);
    Coor v2(0, 0, 1);
    
    std::string str1 = "=.*@#;";
    Cube cube1(st, v0, v1, v2, str1);
    cube1.rotate(Angle(0.6f, 0.3f));

    std::string str2 = "=.*@#;";
    Cube cube2(st, -v0, -v1, -v2, str2);
    cube2.rotate(Angle(0.6f, 0.3f));

    std::string str3 = "=.*@#;";
    Cube cube3(st-(v1/2), v0/2, v1/2, v2/2, str3);
    cube2.rotate(Angle(0.6f, 0.3f));
    // cube3.rotate(Angle(0.6f, 0.3f));

    Square square(Coor(0.5, -1.0, 0.5), (v0/2)+(v1/2), (v1/2)+(v2/2), ')');
    Facebody sqBody(&square);
    sqBody.rotate(Angle(0.6f, 0.3f));

    // Insert Cube
    space.make(cube1, 0);
    space.make(cube2, 1);
    space.make(cube3, 2);
    space.make(sqBody, 3);

    for (;;) {
        // Show
        if (space.show()) { break; }
        std::cout << "terminal fine. press any key to exit" << std::endl;

        // Config
        if (space.config()) { break; }
    }

    return 0;
}