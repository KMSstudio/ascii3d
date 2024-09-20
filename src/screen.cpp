#include "screen.hpp"
#include <iostream>
#include <vector>

// *********************************** /&
//                Pixel                //
// *********************************** //

Pixel::Pixel() : ch(' '), depth(-1), empty(true) {}
Pixel::Pixel(char ch, float depth) : ch(ch), depth(depth), empty(false) {}

char Pixel::get() const { return this->ch; }

// Set pixel by Pixel& pixel. Only work when pixel.depth < this->depth || force
int Pixel::set(const Pixel& pixel, const bool force) {
    if (force || this->empty || pixel.depth < this->depth) {
        this->ch = pixel.ch; this->depth = pixel.depth; this->empty = false; return 1; }
    return 0;
}

// Set pixel by chatt ch, float depth. Only work when depth < this->depth || force
int Pixel::set(char ch, float depth, const bool force) {
    if (force || depth < this->depth || this->empty) { 
        this->ch = ch; this->depth = depth; this->empty = false; return 1; }
    return 0;
}

// Clear the pixel
void Pixel::clear() { this->ch = ' '; this->depth = -1; this->empty = true; }

// ************************************ /&
//                Screen                //
// ************************************ //

Screen::Screen(Coor2d size) : size(size), center(size.x / 2, size.y / 2) { pixels.resize(size.x * size.y); }
Screen::~Screen() { ; }

Pixel Screen::getPixel(const Coor2d& pos) const { return pixels[pos.x + pos.y * size.x]; }
char Screen::prtPixel(const Coor2d& pos) const { return getPixel(pos).get(); }
void Screen::setPixel(const Coor2d& pos, const Pixel& pixel, const bool force) { pixels[pos.x + pos.y * size.x].set(pixel, force); }
void Screen::clsPixel(const Coor2d& pos) { pixels[pos.x + pos.y * size.x].clear(); }

Coor2d Screen::getCenter() const { return this->center; }
Coor2d Screen::getSize() const { return this->size; }

// Clear all pixel in screen
void Screen::clear() {
    for (int y = 0; y < this->size.y; y++) {
        for (int x = 0; x < this->size.x; x++) { clsPixel(Coor2d(x, y)); }
    }
}

// Print screen. use console output
int Screen::print(const int prtByDepth) const {
    for (int y = 0; y < this->size.y; y++) {
        for (int x = 0; x < this->size.x; x++) {
            std::cout << prtPixel(Coor2d(x, y)); }
        std::cout << std::endl;
    }
    return this->size.x * (this->size.y+1);
}

// Print screen as string
std::string Screen::prtExp() const {
        std::string line;
    for (int y = 0; y < this->size.y; y++) {
        for (int x = 0; x < this->size.x; x++) { line += getPixel(Coor2d(x, y)).get(); }
        line += '\n';
    }
    return line;
}