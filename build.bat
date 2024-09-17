@echo off

rem Step 1: Compile each .cpp file to object files
g++ -c src/main.cpp -o obj/main.o
g++ -c src/base.cpp -o obj/base.o
g++ -c src/screen.cpp -o obj/screen.o
g++ -c src/camera.cpp -o obj/camera.o
g++ -c src/face.cpp -o obj/face.o
g++ -c src/body.cpp -o obj/body.o
g++ -c src/space.cpp -o obj/space.o

rem Step 2: Link the object files to create the executable
g++ obj/main.o obj/base.o obj/screen.o obj/camera.o obj/face.o obj/body.o obj/space.o -o ascii3d

rem Step 3: Run the executable
rem ascii3d.exe