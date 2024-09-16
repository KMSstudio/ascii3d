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
    
    // Cube 객체 생성 (문자열 길이가 6 미만일 때)
    std::string str1 = "=.*&%]";  // 각 면에 동일한 문자 'A'
    Cube cube1(st, v0, v1, v2, str1);
    cube1.rotate(Angle(0.6f, 0.3f));

    // Cube 객체 생성 (문자열 길이가 6 이상일 때)
    std::string str2 = "=.*&%]";  // 각 면에 다른 문자
    Cube cube2(st, -v0, -v1, -v2, str2);
    cube2.rotate(Angle(0.6f, 0.3f));

    // Camera, Screen 객체 생성
    Camera camera(25, 1, 50);  // depth = 5, 최소/최대 depth는 각각 1, 10
    Screen screen(Coor2d(40, 40));  // 스크린의 크기 (80x40)

    float unit = sqrtf((40*40)/(2*2*2)) * (2.0f + 20.0f);
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
                    rotation = Angle(-0.1f, 0.0f);  // 왼쪽으로 회전
                    break;
                case 'd':
                    rotation = Angle(0.1f, 0.0f);   // 오른쪽으로 회전
                    break;
                case 'w':
                    rotation = Angle(0.0f, 0.1f);   // 위로 회전
                    break;
                case 's':
                    rotation = Angle(0.0f, -0.1f);  // 아래로 회전
                    break;
                case 'q':  // 프로그램 종료
                    return 0;
            }

            // 큐브 회전 수행
            cube1.rotate(rotation, 0);
            cube2.rotate(rotation, 0);

            // 화면 갱신
            system("cls");
            screen = Screen(Coor2d(40, 40));
            cube1.project(camera, unit, screen);
            cube2.project(camera, unit, screen);
            screen.print();
        }
    }

    return 0;
}
