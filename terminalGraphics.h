#include <vector>
#include <Eigen/Dense>

struct cube{
    float x[8];
    float y[8];
    float z[8];
};

class TerminalGraphics{

int width, height;
float zNear = 1, zFar = 10;
std::vector<std::vector<char>> asciiBlock;
Eigen::Matrix4f perspectiveProjectionMatrix;

public:

void clearScreen();
void renderScreen();
void plotCharacter(int x, int y, char c);
void draw2dLine(int x0, int x1, int y0, int y1, char c);
void drawCube(float xs[8], float ys[8], char c);
void rotateCubeZ(cube &cube, double theta);
void rotateCubeY(cube &cube, double theta);
void rotateCubeX(cube &cube, double theta);
//void draw3dLine(int x0, int x1, int y0, int y1, int z0, int z1, char c);
//Initializes width, height, and the asciiBlock (screen)
TerminalGraphics(int width, int height, int fovDegrees);

};