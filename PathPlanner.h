#include <iostream>
#include <cmath>
#include <queue>
#include <vector>

constexpr float RISK_FACTOR = 10;

class Candidate {
    public:
        Candidate* parent;
        int x;
        int y;
        int risk;
        float airDistance;
        float pathDistance;
        float heuristic;

        Candidate(int x, int y, int risk, int endX, int endY);
        Candidate(Candidate &parent, int xChange, int yChange, int risk, int endX, int endY);
};

int* planPath(int width, int height, int widthStride, int heightStride, int* riskData, int maxRange, int startCoordX, int startCoordY, int endX, int endY);

extern "C" {
    int* planPath_c(int width, int height, int widthStride, int heightStride, int* riskData, int maxRange, int startCoordX, int startCoordY, int endX, int endY);
}
