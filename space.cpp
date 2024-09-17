#include "space.hpp"

// *********************************** /&
//                Space                //
// *********************************** //

// Constructor & Destructor

Space::Space(const Coor& size) : size(size), camera(0x0), screen(0x0), unit(0.0f) {
    for (int i = 0; i < 16; ++i) {
        body[i] = 0x0;
        showBody[i] = 0x0;
    }
}
Space::~Space() {
    for (int i = 0; i < 16; ++i) {
        if (body[i]) delete body[i];
        if (showBody[i]) delete showBody[i];
    }
    if (camera) delete camera;
    if (screen) delete screen;
}

// Initalizing

void Space::setScreen(const Coor2d& screenSize) {
    if (screen) delete screen;
    screen = new Screen(screenSize);
}
void Space::setCamera(float depth, float minDepth, float maxDepth) {
    if (camera) delete camera;
    camera = new Camera(depth, minDepth, maxDepth);
}
int Space::calcUnit() {
    if (!screen || !camera) { return -1; };
    Coor2d screenSize = screen->getSize();
    unit = sqrt((size.x * size.y) / (2 * screenSize.x * screenSize.y)) * (size.x + camera->depth);
}

// (private) _move (for Space::show())

void Space::_move(const char move) {
    Angle rotation(0, 0, 0);
    float angleUnit = 0.2f;
    switch (move) {
        case 'w': case 'W': rotation = Angle(0.0f, -angleUnit); break;      // up
        case 's': case 'S': rotation = Angle(0.0f, +angleUnit); break;      // down
        case 'a': case 'A': rotation = Angle(-angleUnit, 0.0f); break;      // left
        case 'd': case 'D': rotation = Angle(angleUnit, 0.0f); break;       // right
        case 'i': case 'I': camera->act('i'); break;                        // zoom in
        case 'k': case 'K': camera->act('k'); break;                        // zoom out
        case 'j': case 'J': rotation = Angle(0.0f, 0.0f, +angleUnit); break;    // z-rotate
        case 'l': case 'L': rotation = Angle(0.0f, 0.0f, -angleUnit); break;    // z-rotate
        default: break;
    }
}

// Config

int Space::make(const Body& newBody, int index) {
    if (index >= 0 && index < 16) {
        if (body[index] == 0x0) { body[index] = new Body(newBody); return 0; }
        return -1;
    }

    for (int i = 0; i < 16; ++i) {
        if (body[i] == 0x0) { body[i] = new Body(newBody); return 0; } }
    return -1;
}

// Show

int Space::show() {
    if (!screen || !camera || unit == 0.0f) return -1;

    // Loading
    for (int i = 0; i < 16; ++i) { showBody[i] = body[i]; }

    // Show
    char input;
    for (;;) {
        // Print
        screen->clear();
        for (int i = 0; i < 16; ++i) {
            if (showBody[i]) { showBody[i]->project(*camera, unit, *screen); } }
        screen->print();

        // Pause & Move
        input = _getch();
        if (input == 'q' || input == 'Q') { break; }
    }
    return 0;
}