#include "PathPlanner.h"

Candidate::Candidate(int x, int y, int risk, int endX, int endY) {

}

Candidate::Candidate(Candidate &parent, int xChange, int yChange, int risk, int endX, int endY) {

}

int Candidate::compareTo(Candidate &other) {
    return 0;
}

int* planPath(int width, int height, int widthStride, int heightStride, float* riskData, int maxRange, int startCoordX, int startCoordY, int endX, int endY) {
    std::cout << "Hello!" << std::endl;
    return new int[0];
}

extern "C" {
    int* planPath_c(int width, int height, int widthStride, int heightStride, float* riskData, int maxRange, int startCoordX, int startCoordY, int endX, int endY) {
        return planPath(width, height, widthStride, heightStride, riskData, maxRange, startCoordX, startCoordY, endX, endY);
    }
}
