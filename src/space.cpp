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
    std::cout << "Destructor started..." << std::endl;
    for (int i = 0; i < 16; ++i) {
        if (body[i]) { 
            std::cout << "Destruct body[" << i << "]" << std::endl;
            delete body[i];
        }
    }
    if (camera) { std::cout << "Destruct Camera\n"; delete camera; }
    if (screen) { std::cout << "Destruct Screen\n"; delete screen; }
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
    unit = 0.5 * sqrtf((screenSize.x * screenSize.y / 4) / (this->size.x * this->size.y)) * (size.x + camera->depth);
    return 0;
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
    for (int i = 0; i < 16; ++i) {
        if (showBody[i]) { showBody[i]->rotate(rotation); } }
    return;
}

// Make

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

int Space::show(int verbose) {
    int res = 0;
    if (!screen || !camera || unit == 0.0f) return -1;

    // Load
    for (int i = 0; i < 16; ++i) {
        if (body[i]) { showBody[i] = new Body(*body[i]); } }
    
    // Print
    system("cls");
    screen->clear();
    for (int i = 0; i < 16; ++i) {
        if (showBody[i]) { showBody[i]->project(*camera, unit, *screen); } }
    screen->print();

    // Show
    char input;
    for (;;) {
        if (_kbhit()) {
            // Move
            input = _getch();
            if (input == 'q' || input == 'Q') { res = 0; break; }
            if (input == 'x' || input == 'X') { res = 1; break; }
            _move(input);

            // Print
            system("cls");
            screen->clear();
            for (int i = 0; i < 16; ++i) {
                if (showBody[i]) { showBody[i]->project(*camera, unit, *screen); } }
            std::cout << screen->prtExp() << std::endl;
            if (verbose) { 
                Coor2d screenSize = screen->getSize();
                std::cout << "CameraDepth: [" << this->camera->depth << "]  ScreenSize: [" << screenSize.x << ", " << screenSize.y << "] Unit: [" << this->unit << ']'; }
            _flushall();
        }
    }

    // Free
    for (int i = 0; i < 16; ++i) {
        if (showBody[i]) { delete showBody[i]; showBody[i] = 0x0; } }
    return res;
}

int Space::config() {
    return 0;
}