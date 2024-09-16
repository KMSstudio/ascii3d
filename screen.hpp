#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
#include <vector>
#include "base.hpp"

class Pixel {
private:
    char ch;
    float depth;
    bool empty;

public:
    Pixel();
    Pixel(char ch, float depth);
    
    char get() const;

    int set(const Pixel& pixel);
    int set(char ch, float depth);
};

class Screen {
private:
    std::vector<Pixel> pixels;
    Coor2d size;
    Coor2d center;

public:
    Screen(Coor2d size);
    ~Screen();
    
    Pixel getPixel(const Coor2d& pos) const;
    char prtPixel(const Coor2d& pos) const;
    void setPixel(const Coor2d& pos, const Pixel& pixel);
    
    Coor2d getCenter() const;

    int print(const int prtByDepth = 0) const;
};

#endif