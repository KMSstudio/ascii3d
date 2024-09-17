#include "body.hpp"
#include "camera.hpp"
#include "screen.hpp"
#include <iostream>
#include <conio.h>
#include <windows.h>

int main() {
    // 시작 좌표 st와 3개의 벡터 정의
    Coor st(0, 0, 0);
    Coor v0(1, 0, 0);
    Coor v1(0, 1, 0);
    Coor v2(0, 0, 1);
    
    std::string str1 = "=.*@#;";  // 각 면에 동일한 문자 'A'
    Cube cube1(st, v0, v1, v2, str1);
    cube1.rotate(Angle(0.6f, 0.3f));

    std::string str2 = "=.*@#;";  // 각 면에 다른 문자
    Cube cube2(st, -v0, -v1, -v2, str2);
    cube2.rotate(Angle(0.6f, 0.3f));

    std::string str3 = "=.*@#;";  // 각 면에 다른 문자
    Cube cube3(st-(v1/2), v0/2, v1/2, v2/2, str3);
    cube2.rotate(Angle(0.6f, 0.3f));
    // cube3.rotate(Angle(0.6f, 0.3f));

    Triangle triangle(Coor(0.5, -1, 0.5), Coor(0.5, 0.5, 0), Coor(0, 0.5, 0.5), '@');
    triangle.rotate(Angle(0.6f, 0.3f));

    // Camera, Screen 객체 생성
    Camera camera(25, 10, 50);  // depth = 5, 최소/최대 depth는 각각 1, 10
    Screen screen(Coor2d(100, 100));  // 스크린의 크기 (80x40)
    Screen screenXor(Coor2d(100, 100));

    float unit = sqrtf((100*100)/(2*2*2)) * (2.0f + 20.0f);
    // sqrt((screen.center.x*screen.center.y / space.x*space.y)*arearatio) * (space.z+camera.depth)

    // 큐브 초기 출력
    cube1.project(camera, unit, screen);
    cube2.project(camera, unit, screen);
    screen.print();

    // 메인 루프: 키 입력을 받아 큐브 회전
    Angle rotation(0.0f, 0.0f);  // 회전 각도 초기화
    while (true) {
        if (_kbhit()) {  // 키보드 입력이 있을 때
            char input = _getch();  // 키 입력 받기

            // 'a', 'd', 'w', 's' 키에 따라 회전 각도 설정
            switch (input) {
                case 'a':
                    rotation = Angle(-0.25f, 0.0f);  // 왼쪽으로 회전
                    break;
                case 'd':
                    rotation = Angle(0.25f, 0.0f);   // 오른쪽으로 회전
                    break;
                case 'w':
                    rotation = Angle(0.0f, -0.25f);   // 위로 회전
                    break;
                case 's':
                    rotation = Angle(0.0f, +0.25f);  // 아래로 회전
                    break;
                case 'i':
                    rotation = Angle(0.0f, +0.0f);
                    camera.act('i');
                    break;
                case 'k':
                    rotation = Angle(0.0f, +0.0f);
                    camera.act('j');
                    break;
                case 'j':
                    rotation = Angle(0.0f, 0.0f, +0.25f);
                    break;
                case 'l':
                    rotation = Angle(0.0f, 0.0f, -0.25f);
                    break;
                case 'q':
                    return 0;
            }

            // 큐브 회전 수행
            cube1.rotate(rotation, 0);
            cube2.rotate(rotation, 0);
            cube3.rotate(rotation, 0);
            triangle.rotate(rotation);

            // 화면 갱신
            system("cls");
            screenXor = Screen(Coor2d(100, 100));
            cube1.project(camera, unit, screenXor);
            cube2.project(camera, unit, screenXor);
            cube3.project(camera, unit, screenXor);
            triangle.project(camera, unit, screenXor);
            // screen.prtXor(screenXor);
            std::cout << screenXor.prtExp() << std::endl;
            std::cout << camera.depth << std::endl;
        }
    }

    return 0;
}
