#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <math.h>
#include "terminalGraphics.h"

void TerminalGraphics::clearScreen(){
    for(int i = 0; i < height; i++){
        for(int k = 0; k < width; k++){
            asciiBlock[i][k] = ' ';
        }
    }
}

void TerminalGraphics::renderScreen(){
    for(int i = 0; i < height; i++){
        for(int k = 0; k < width; k++){
            std::cout << asciiBlock[i][k] << " " << " ";
        }
        std::cout << "\n";
    }
}

void doNothing(){
}

void TerminalGraphics::plotCharacter(int x, int y, char c){
    x += 0;
    y += 0;

    if(x >= 0 && x <= 99 && y >= 0 && y <= 74){
        asciiBlock[y][x] = c;
    }
}

void TerminalGraphics::draw2dLine(int x0, int x1, int y0, int y1, char c){ //Figure this out later lol
    int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        plotCharacter(x0, y0, c);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void TerminalGraphics::drawCube(float xs[8], float ys[8], char c){
    draw2dLine((int)xs[0], (int)xs[1], (int)ys[0], (int)ys[1], c);
    draw2dLine((int)xs[1], (int)xs[2], (int)ys[1], (int)ys[2], c);
    draw2dLine((int)xs[2], (int)xs[3], (int)ys[2], (int)ys[3], c);
    draw2dLine((int)xs[3], (int)xs[0], (int)ys[3], (int)ys[0], c);

    // Top face
    draw2dLine((int)xs[4], (int)xs[5], (int)ys[4], (int)ys[5], c);
    draw2dLine((int)xs[5], (int)xs[6], (int)ys[5], (int)ys[6], c);
    draw2dLine((int)xs[6], (int)xs[7], (int)ys[6], (int)ys[7], c);
    draw2dLine((int)xs[7], (int)xs[4], (int)ys[7], (int)ys[4], c);

    // Connecting edges
    draw2dLine((int)xs[0], (int)xs[4], (int)ys[0], (int)ys[4], c);
    draw2dLine((int)xs[1], (int)xs[5], (int)ys[1], (int)ys[5], c);
    draw2dLine((int)xs[2], (int)xs[6], (int)ys[2], (int)ys[6], c);
    draw2dLine((int)xs[3], (int)xs[7], (int)ys[3], (int)ys[7], c);

}

void TerminalGraphics::rotateCubeX(cube &cube){
    Eigen::Matrix3f rotationMatrix;
    rotationMatrix << 1, 0, 0,
                    0, (float)sin(.03), (float)cos(.03),
                    0, (float)cos(.03), (float)-sin(.03);

    for(int i = 0; i < 8; i++){
        Eigen::Vector3f original;
        original << cube.x[i], cube.y[i], cube.z[i];
        Eigen::Vector3f transformed = rotationMatrix * original;
        cube.x[i] = transformed[0];
        cube.y[i] = transformed[1];
        cube.z[i] = transformed[2];
    }
}

void TerminalGraphics::rotateCubeY(cube &cube){
    Eigen::Matrix3f rotationMatrix;
    rotationMatrix << (float)sin(.01), 0, (float)cos(.01),
                    0, 1, 0,
                    (float)cos(.01), 0, (float)-sin(.01);

    for(int i = 0; i < 8; i++){
        Eigen::Vector3f original;
        original << cube.x[i], cube.y[i], cube.z[i];
        Eigen::Vector3f transformed = rotationMatrix * original;
        cube.x[i] = transformed[0];
        cube.y[i] = transformed[1];
        cube.z[i] = transformed[2];
    }
}

// void TerminalGraphics::draw3dLine(int x0, int x1, int y0, int y1, int z0, int z1, char c){
//     //multiply this by the prospective matrix
//     Eigen::Vector4f 2dVertexA << x0, y0;
//     Eigen::Vector4f 2dVertexB << x1, y1;
//     draw2dLine(2dVertexA., c);
// }

//Initializes width, height, and the asciiBlock (screen)
TerminalGraphics::TerminalGraphics(int width, int height, int fovDegrees){
    this->width = width;
    this->height = height;
    asciiBlock.reserve(height);
    for(int i = 0; i < height; i++){
        std::vector<char> vec;
        vec.resize(width, ' '); //TRY AND REFACTOR THIS LATER!!!
        asciiBlock.push_back(vec);
    }
    float a = ((float) height) / ((float) width);
    float f = ((float)1)/(float)atan(1/fovDegrees);
    float q = zFar / ((float) (zFar-zNear));
    perspectiveProjectionMatrix << a*f, 0, 0, 0,
                               0, f, 0, 0,
                               0, 0, q, 1,
                               0, 0, -zNear*q, 0; 
}