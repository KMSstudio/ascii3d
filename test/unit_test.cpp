#include "../src/screen.hpp" // Include screen.hpp from src directory
#include <iostream>
#include <cassert>
#include <chrono>

// Test Pixel class
void testPixel() {
    auto start = std::chrono::high_resolution_clock::now(); // Start timer
    
    // Test default constructor
    Pixel p1;
    assert(p1.get() == ' ');
    
    // Test parameterized constructor
    Pixel p2('A', 1.0f);
    assert(p2.get() == 'A');
    
    // Test set method (force=false)
    Pixel p3;
    p3.set('B', 0.5f, false);
    assert(p3.get() == 'B');
    
    // Test depth comparison
    assert(p3.set('C', 0.8f, false) == 0); // Depth is larger, no change
    assert(p3.get() == 'B');
    
    // Test force=true
    assert(p3.set('C', 0.8f, true) == 1);
    assert(p3.get() == 'C');
    
    // Test clear method
    p3.clear();
    assert(p3.get() == ' ');
    
    auto end = std::chrono::high_resolution_clock::now(); // End timer
    std::chrono::duration<double> elapsed = end - start;
    
    std::cout << "Pixel tests passed! Time taken: " << elapsed.count() << " seconds" << std::endl;
}

// Test Screen class
void testScreen() {
    auto start = std::chrono::high_resolution_clock::now(); // Start timer

    // Test screen creation
    Coor2d size(5, 5);
    Screen screen(size);
    assert(screen.getSize().x == 5);
    assert(screen.getSize().y == 5);
    
    // Test setting a pixel
    Pixel p('X', 1.0f);
    Coor2d pos(2, 2);
    screen.setPixel(pos, p, false);
    assert(screen.getPixel(pos).get() == 'X');
    
    // Test force=false
    Pixel p2('Y', 2.0f);
    screen.setPixel(pos, p2, false);
    assert(screen.getPixel(pos).get() == 'X'); // Depth is larger, no change
    
    // Test force=true
    screen.setPixel(pos, p2, true);
    assert(screen.getPixel(pos).get() == 'Y');
    
    // Test screen clear
    screen.clear();
    assert(screen.getPixel(pos).get() == ' ');
    
    // Test screen output
    std::cout << "Screen output test (should be empty):" << std::endl;
    screen.print(0); // Should print an empty screen
    
    auto end = std::chrono::high_resolution_clock::now(); // End timer
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Screen tests passed! Time taken: " << elapsed.count() << " seconds" << std::endl;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now(); // Start timer

    // Test Pixel class
    testPixel();

    // Test Screen class
    testScreen();

    auto end = std::chrono::high_resolution_clock::now(); // End timer
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "All tests completed! Total time taken: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}