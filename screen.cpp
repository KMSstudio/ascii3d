#include "screen.hpp"
#include <iostream>
#include <vector>
#include <windows.h>

static void gotoxy(int x, int y) {
    COORD pos = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// *********************************** /&
//                Pixel                //
// *********************************** //

Pixel::Pixel() : ch(' '), depth(-1), empty(true) {}
Pixel::Pixel(char ch, float depth) : ch(ch), depth(depth), empty(false) {}

char Pixel::get() const { return this->ch; }

int Pixel::set(const Pixel& pixel, const bool force) {
    if (force || this->empty || pixel.depth < this->depth) {
        this->ch = pixel.ch;
        this->depth = pixel.depth;
        this->empty = false;
        return 1;
    }
    return 0;
}

int Pixel::set(char ch, float depth, const bool force) {
    if (force || depth < this->depth || this->empty) {
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
void Screen::setPixel(const Coor2d& pos, const Pixel& pixel, const bool force) { pixels[pos.x + pos.y * size.x].set(pixel, force); }

Coor2d Screen::getCenter() const { return this->center; }
Coor2d Screen::getSize() const { return this->size; }

int Screen::print(const int prtByDepth) const {
    for (int y = 0; y < this->size.y; ++y) {
        for (int x = 0; x < this->size.x; ++x) {
            std::cout << prtPixel(Coor2d(x, y)); }
        std::cout << std::endl;
    }
    return this->size.x * (this->size.y+1);
}

std::string Screen::prtExp() const {
        std::string line;
    for (int y = 0; y < this->size.y; ++y) {
        for (int x = 0; x < this->size.x; ++x) { line += getPixel(Coor2d(x, y)).get(); }
        line += '\n';
    }
    return line;
}