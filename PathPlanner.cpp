#include "PathPlanner.h"

Candidate::Candidate(int x, int y, int risk, int endX, int endY) {
    this->parent = nullptr;
    this->x = x;
    this->y = y;
    this->risk = risk;
    this->airDistance = std::sqrt((endX - x) * (endX - x) + (endY - y) + (endY - y));
    this->pathDistance = 0;
    this->heuristic = risk * RISK_FACTOR + airDistance + pathDistance;
}

Candidate::Candidate(Candidate &parent, int xChange, int yChange, int risk, int endX, int endY) {
    this->parent = &parent;
    this->x = parent.x + xChange;
    this->y = parent.y + yChange;
    this->risk = parent.risk + risk;
    this->airDistance = std::sqrt((endX - x) * (endX - x) + (endY - y) + (endY - y));
    this->pathDistance = parent.pathDistance + 
        ((xChange != 0 && yChange != 0) ? std::sqrt(2) : 1);
    this->heuristic = risk * RISK_FACTOR + airDistance + pathDistance;
}

int Candidate::compareTo(Candidate &other) {
    return this->heuristic - other.heuristic;
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
