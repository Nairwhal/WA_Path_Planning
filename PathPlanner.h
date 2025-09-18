#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <unordered_set>

constexpr float RISK_FACTOR = 10;

class Candidate {
    public:
        Candidate* parent;
        int x;
        int y;
        double risk;
        float airDistance;
        float pathDistance;
        float heuristic;

        Candidate(int x, int y, double risk, int endX, int endY);
        Candidate(Candidate *parent, int xChange, int yChange, double risk, int endX, int endY);
};

int* planPath(int width, int height, double* riskData, int maxRange, int startCoordX, int startCoordY, int endX, int endY);

extern "C" {
    int* planPath_c(int width, int height, double* riskData, int maxRange, int startCoordX, int startCoordY, int endX, int endY);
}
