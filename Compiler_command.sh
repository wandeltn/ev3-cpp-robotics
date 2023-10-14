docker run --rm -it -v ./:/src -w /src ev3cc
arm-linux-gnueabi-g++ -pthread -Wall -std=c++17 -o bin/main main.cpp include/display/Screen.cpp include/display/Window.cpp include/display/DirectRenderingManager.cpp ev3dev.cpp include/io/Ports.cpp include/Field.cpp include/

sudo docker run --rm -it --mount type=bind,source="$(pwd)",target=/src ev3cc
clear && arm-linux-gnueabi-g++ -Wall -Wno-psabi -std=c++17 -o bin/main $(find . -type f -name '*.cpp')