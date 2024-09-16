#include "face.hpp"  // Coor, Angle 클래스 포함
#include "screen.hpp"  // Screen 클래스 포함
#include "camera.hpp"  // Camera 클래스 포함
#include <iostream>
#include <cmath>

int main() {
    // Coor 객체 초기화
    Coor point1(-3.0f, -3.0f, 0.0f);
    Coor point2(3.0f, -3.0f, 0.0f);
    Coor point3(3.0f, 3.0f, 0.0f);
    Coor point4(-3.0f, 3.0f, 0.0f);

    Coor point5(-3.0f, -3.0f, 5.0f);
    Coor point6(3.0f, -3.0f, 5.0f);
    Coor point7(3.0f, 3.0f, 5.0f);
    Coor point8(-3.0f, 3.0f, 5.0f);

    Square square1(Coor(-3.0f, -3.0f, 5.0f), Coor(-3.0f, 3.0f, 5.0f), Coor(3.0f, -3.0f, 5.0f), '&');
    Face* sq1 = &square1;
    // Square square2(Coor(-3.0f, -3.0f, 5.0f), Coor(-3.0f, -3.0f, 0.0f), Coor(3.0f, -3.0f, 5.0f), '~');
    Square square2(Coor(-3.0f, -3.0f, 5.0f), Coor(-3.0f, -3.0f, 0.0f), Coor(3.0f, -3.0f, 5.0f), '~');

    square1.rotate(Angle(0.0f, 0.0f));
    square2.rotate(Angle(0.0f, 0.0f));

    float unit = sqrtf((10*10)/(5*5*2)) * (3.0f + 10.0f);
    // sqrt((screen.center.x*screen.center.y / space.x*space.y)*arearatio) * (space.z+camera.depth)

    Camera camera(10.0f, 1.0f, 20.0f);  // 카메라 깊이 10, 최소 깊이 1, 최대 깊이 20
    Screen screen(Coor2d(20, 20));  // 80x40 크기의 스크린 생성
    std::cout << unit << std::endl;

    char pixelChar = '*';
    if (point1.project(camera, pixelChar, unit, screen) == 0) {
        point2.project(camera, pixelChar, unit, screen);
        point3.project(camera, pixelChar, unit, screen);
        point4.project(camera, pixelChar, unit, screen);
        
        // point5.project(camera, '&', unit, screen);
        // point6.project(camera, '&', unit, screen);
        // point7.project(camera, '&', unit, screen);
        // point8.project(camera, '&', unit, screen);

        sq1->project(camera, unit, screen);
        square2.project(camera, unit, screen);

        std::cout << "Point projected successfully on screen.\n";
        screen.print();  // 스크린에 투영된 결과를 출력
    } else {
        std::cout << "Point projection failed.\n";
    }

    return 0;
}