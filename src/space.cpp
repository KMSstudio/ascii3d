#include "space.hpp"

// *********************************** /&
//                Space                //
// *********************************** //

// Constructor & Destructor

Space::Space(const Coor& size) : size(size), camera(0x0), screen(0x0), unit(0.0f) {
    for (int i = 0; i < 16; i++) {
        body[i] = 0x0;
        showBody[i] = 0x0;
    }
}
Space::~Space() {
    for (int i = 0; i < 16; i++) { if (body[i]) {  delete body[i]; } }
    if (camera) { delete camera; }
    if (screen) { delete screen; }
}

// Initalizing

void Space::setScreen(const Coor2d& screenSize) {
    if (screen) delete screen;
    screen = new Screen(screenSize);
    _calc();
}
void Space::setCamera(float depth, float minDepth, float maxDepth) {
    if (camera) delete camera;
    camera = new Camera(depth, minDepth, maxDepth);
    _calc();
}

// (private) _calc (for calculation of unit)
int Space::_calc() {
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
    for (int i = 0; i < 16; i++) {
        if (showBody[i]) { showBody[i]->rotate(rotation); } }
    return;
}

static void coorInput(Coor& coor) {
    cout << "x: "; cin >> coor.x;
    cout << "y: "; cin >> coor.y;
    cout << "z: "; cin >> coor.z;
    return;
}

// (private) _config (for Space::config())
void Space::_config(const string& config) {
    if (config == "HELP" || config == "H") {
        cout << left << setw(8) << "HELP" << ": Show available command list" << endl;
        cout << left << setw(8) << "LIST" << ": Show information about current Space, Camera and Objects" << endl;
        cout << endl;
        cout << left << setw(8) << "MAKE" << ": Make new object" << endl;
        cout << endl;
        cout << left << setw(16) << "QUIT|SHOW" << ": Quit a config window and start show window" << endl;
        cout << left << setw(16) << "EXIT|TERM" << ": Exit a program" << endl;
        cout << endl;
    }
    else if (config == "LIST" || config == "L") {
        cout << endl << "< Space  >" << endl;
        cout << left << setw(8) << "Unit: " << unit << endl;
        cout << left << setw(8) << "Size: " << '(' << size.x << ", " << size.y << ", " << size.z << ')' << endl;
        
        cout << endl << "< Camera >" << endl;
        cout << left << setw(20) << "CameraDepth: " << camera->depth << endl;
        cout << left << setw(20) << "CameraMaxDepth: " << camera->getDepthMax() << endl;
        cout << left << setw(20) << "CameraMinDepth: " << camera->getDepthMin() << endl;

        cout << endl << "< Object >" << endl;
        for(int i = 0; i < 16; i++) {
            cout << hex << i << ": " << left << setw(20) << body[i] << ((i%2)?'\n':' '); }
        cout << dec << endl;
    }
    else if (config == "CREATE" || config == "C") { _make(); }
    else if (config == "DROP" || config == "D") {
        int index;
        cout << "Index to drop: "; cin >> index;
        if (index < 0 || index > 15) { cout << "Invalid index " << index << endl; return; }

        if (body[index]) { delete body[index]; body[index] = 0x0; }
        cout << "Drop body " << index << endl;
    }
    else if (config == "ALTER" || config == "A") {
        int index;
        cout << "Index to alter: "; cin >> index;
        if (index < 0 || index > 15) { cout << "Invalid index " << index << endl; return; }

        if (body[index]) { delete body[index]; body[index] = 0x0; }
        cout << "Make new body to alter..." << endl;
        _make(index);
    }
    else { cout << "Invalid command: " << config << endl; }
    return;
}

// (private) _make (for Space::_config())
void Space::_make(int index) {
    int type;

    char ch;
    string fillCh;

    Square sqtmp;
    Triangle trtmp;
    Coor st, v0, v1, v2;

    cout << endl << "< Make   >" << endl;

    // Get index
    if (index == -2) {
        cout << endl << "Index" << endl;
        cout << "Index to input (index must be empty, -1 for default slot): "; cin >> index;
        if (body[index]) { cout << "Invalid: body[index] does not empty" << endl; return; }
    }

    // Get type
    cout << endl << "Type of Body" << endl;
    cout << left << setw(12) << "Cube:" << 10 << endl;
    cout << left << setw(12) << "Square:" << 21 << endl;
    cout << left << setw(12) << "Triangle:" << 22 << endl;
    cout << "  " << left << setw(15) << "type?: "; cin >> type;

    switch (type) {
        // Cube
        case 10:
        cout << endl << "Start coor for Cube" << endl; coorInput(st);
        cout << "vector 0" << endl; coorInput(v0);
        cout << "vector 1" << endl; coorInput(v1);
        cout << "vector 2" << endl; coorInput(v2);
        cout << endl << "Fill" << endl;
        cout << "(Each face will fill with input[0], input[1], ... input[5]): "; cin >> fillCh;

        this->make(Cube(st, v0, v1, v2, fillCh), index);
        cout << "Make cube to slot " << index << endl;
        break;

        // Square
        case 21:
        cout << endl << "Start coor for Square" << endl; coorInput(st);
        cout << "vector 0" << endl; coorInput(v0);
        cout << "vector 1" << endl; coorInput(v1);
        cout << endl << "Fill" << endl;
        cout << "(The face will fill with input(char) ): "; cin >> ch;

        sqtmp = Square(st, v0, v1, ch);
        this->make(Facebody(&sqtmp), index);
        cout << "Make square to slot " << index << endl;
        break;

        // Triangle
        case 22:
        cout << endl << "Start coor for Triangle" << endl; coorInput(st);
        cout << "vector 0" << endl; coorInput(v0);
        cout << "vector 1" << endl; coorInput(v1);
        cout << endl << "Fill" << endl;
        cout << "(The face will fill with input(char) ): "; cin >> ch;

        trtmp = Triangle(st, v0, v1, ch);
        this->make(Facebody(&trtmp), index);
        cout << "Make Triangle to slot " << index << endl;
        break;

        default:
        cout << "Invalid object number: " << type << endl;
        break;
    }
}

// Make
int Space::make(const Body& newBody, int index) {
    if (index >= 0 && index < 16) {
        if (body[index] == 0x0) { body[index] = new Body(newBody); return 0; }
        return -1;
    }

    for (int i = 0; i < 16; i++) {
        if (body[i] == 0x0) { body[i] = new Body(newBody); return 0; } }
    return -1;
}

// Show
int Space::show(int verbose) {
    int res = 0;
    if (!screen || !camera || unit == 0.0f) return -1;

    // Load
    for (int i = 0; i < 16; i++) {
        if (body[i]) { showBody[i] = new Body(*body[i]); } }
    
    // Print
    system("cls");
    screen->clear();
    for (int i = 0; i < 16; i++) {
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
            for (int i = 0; i < 16; i++) {
                if (showBody[i]) { showBody[i]->project(*camera, unit, *screen); } }
            cout << screen->prtExp() << endl;
            if (verbose) { 
                Coor2d screenSize = screen->getSize();
                cout << "CameraDepth: [" << this->camera->depth << "]  ScreenSize: [" << screenSize.x << ", " << screenSize.y << "] Unit: [" << this->unit << ']'; }
            _flushall();
        }
    }

    // Free
    for (int i = 0; i < 16; i++) {
        if (showBody[i]) { delete showBody[i]; showBody[i] = 0x0; } }
    return res;
}

int Space::config() {int res = 0;
    system("cls");
    cout << "Welcome to enter Config station" << endl;

    // Loop
    string input;
    for (;;) {
        // Input
        cout << "cmd> ";
        cin >> input;
        for (auto& c: input) { c = toupper(c); }
        if (input == "SHOW" || input == "QUIT" || input == "Q") { res = 0; break; }
        if (input == "TERM" || input == "EXIT" || input == "X") { res = 1; break; }

        // Config
        system("cls");
        _config(input);
        _flushall();
    }

    // Terminate
    return res;
}