#include "screen.hpp"
#include <iostream>

int main() {
    Coor2d screenSize(10, 5);
    Screen screen(screenSize);

    // Using the constructor to set initial values
    Pixel p1('*', 0.5);
    
    // Using the new set function with ch and depth
    Pixel p2;
    p2.set('#', 0.2);

    screen.setPixel(Coor2d(2, 2), p1);
    screen.setPixel(Coor2d(5, 3), p2);

    // Print the screen
    screen.print();

    return 0;
}