#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
#include <vector>
#include "base.hpp"

static void gotoxy(int x, int y);

class Pixel {
private:
    char ch;
    float depth;
    bool empty;

public:
    Pixel();
    Pixel(char ch, float depth);
    
    char get() const;

    int set(const Pixel& pixel, const bool force=0);
    int set(char ch, float depth, const bool force=0);

    void clear();
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
    void setPixel(const Coor2d& pos, const Pixel& pixel, const bool force=0);
    void clsPixel(const Coor2d& pos);
    
    Coor2d getCenter() const;
    Coor2d getSize() const;

    void clear();
    int print(const int prtByDepth = 0) const;
    std::string prtExp() const;
};

#endif