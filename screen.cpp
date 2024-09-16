#include "screen.hpp"
#include <iostream>
#include <vector>

// *********************************** /&
//                Pixel                //
// *********************************** //

Pixel::Pixel() : ch(' '), depth(-1), empty(true) {}
Pixel::Pixel(char ch, float depth) : ch(ch), depth(depth), empty(false) {}

char Pixel::get() const { return this->ch; }

int Pixel::set(const Pixel& pixel) {
    if (pixel.depth < this->depth || this->empty) {
        this->ch = pixel.ch;
        this->depth = pixel.depth;
        this->empty = false;
        return 1;
    }
    return 0;
}

int Pixel::set(char ch, float depth) {
    if (depth < this->depth || this->empty) {
        this->ch = ch;
        this->depth = depth;
        this->empty = false;
        return 1;
    }
    return 0;
}

// ************************************ /&
//                Screen                //
// ************************************ //

Screen::Screen(Coor2d size) : size(size), center(size.x / 2, size.y / 2) { pixels.resize(size.x * size.y); }
Screen::~Screen() { ; }

Pixel Screen::getPixel(const Coor2d& pos) const { return pixels[pos.x + pos.y * size.x]; }
char Screen::prtPixel(const Coor2d& pos) const { return getPixel(pos).get(); }
void Screen::setPixel(const Coor2d& pos, const Pixel& pixel) { pixels[pos.x + pos.y * size.x].set(pixel); }

Coor2d Screen::getCenter() const { return this->center; }
Coor2d Screen::getSize() const {return this->size; }

int Screen::print(const int prtByDepth) const {
    for (int y = 0; y < this->size.y; ++y) {
        for (int x = 0; x < this->size.x; ++x) {
            std::cout << prtPixel(Coor2d(x, y)); }
        std::cout << std::endl;
    }
    return this->size.x * (this->size.y+1);
}