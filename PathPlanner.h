#include <iostream>

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

        int compareTo(Candidate &other);
};

int* planPath(int width, int height, int widthStride, int heightStride, float* riskData, int maxRange, int startCoordX, int startCoordY, int endX, int endY);

extern "C" {
    int* planPath_c(int width, int height, int widthStride, int heightStride, float* riskData, int maxRange, int startCoordX, int startCoordY, int endX, int endY);
}
