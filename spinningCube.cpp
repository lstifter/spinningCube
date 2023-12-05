#include "terminalGraphics.h"
#include <cstdlib>
#include <iostream>
#include <Eigen/Dense>
#include <chrono>
#include <thread>

const int HEIGHT = 75;
const int WIDTH = 100;

int main(){
    std::ios::sync_with_stdio(false);
    TerminalGraphics graphics(WIDTH,HEIGHT,120);
    // graphics.draw2dLine(1,180,3,140,'&');
    // graphics.draw2dLine(30,195,140,3, '@');
    // float xs[8] = {50,100,50,100,50,100,50,100};
    // float ys[8] = {50,50,100,100,50,50,100,100};
    // float zs[8] = {50,50,50,50,100,100,100,100};
    // cube cube = {{25,50,50,25,25,50,50,25}, //x
    //              {25,25,50,50,25,25,50,50}, //y
    //              {25,25,25,25,50,50,50,50}};//z

    cube cube2 = {{-5, 5, 5, -5, -5, 5, 5, -5}, {-5, -5, 5, 5, -5, -5, 5, 5}, {-5, -5, -5, -5, 5, 5, 5, 5}}; //xyz
    cube cube3 = {{-15, 15, 15, -15, -15, 15, 15, -15}, {-15, -15, 15, 15, -15, -15, 15, 15}, {-15, -15, -15, -15, 15, 15, 15, 15}};
    // graphics.drawCube(cube.x, cube.y, '$');
    // graphics.rotateCubeX(cube);
    // graphics.rotateCubeY(cube);
    // std::cout << "\n";
    // graphics.drawCube(cube.x,cube.y,'$');
    // graphics.renderScreen();
    constexpr std::chrono::milliseconds timestep(10000000);

auto previousTime = std::chrono::steady_clock::now();
auto lag = std::chrono::milliseconds(0);

while (true) { // Replace with your game's quit condition
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = currentTime - previousTime;
    previousTime = currentTime;
    lag += std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime);

    // Update Game State as many times as necessary for the accumulated lag
    while (lag >= timestep) {
        lag -= timestep;
    }
    graphics.clearScreen();
    std::cout << std::endl;
    // graphics.draw2dLine(-WIDTH / 2,WIDTH / 2, -HEIGHT / 2,HEIGHT / 2, '$');
    // graphics.draw2dLine(0,0,0,0,'a');
    graphics.rotateCubeX(cube2, .02);
    graphics.rotateCubeY(cube2, .01);

    graphics.rotateCubeX(cube3, .01);
    graphics.rotateCubeY(cube3, .02);

    graphics.drawCube(cube2.x, cube2.y, '0');
    graphics.drawCube(cube3.x, cube3.y, '0');
    // system("clear");
    std::cout << "\x1b[H";
    graphics.renderScreen();

    // Sleep if necessary to maintain frame rate
    auto end = std::chrono::steady_clock::now();
    auto frameDuration = end - currentTime;
    // if (frameDuration < timestep) {
    //     std::this_thread::sleep_for(timestep - frameDuration);
    // }
}
    return 0;
}