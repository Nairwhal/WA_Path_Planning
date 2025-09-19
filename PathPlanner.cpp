#include "PathPlanner.h"

//Creates the first candidate (i.e. uses the starting coordinates)
Candidate::Candidate(int x, int y, double risk, int endX, int endY) {
    this->parent = nullptr;
    this->x = x;
    this->y = y;
    this->risk = risk;
    this->airDistance = std::sqrt((endX - x) * (endX - x) + (endY - y) * (endY - y));
    this->pathDistance = 0;
    this->heuristic = risk * RISK_FACTOR + airDistance + pathDistance;
}

//Creates a child candidate
Candidate::Candidate(Candidate *parent, int xChange, int yChange, double risk, int endX, int endY) {
    this->parent = parent;
    this->x = parent->x + xChange;
    this->y = parent->y + yChange;
    this->risk = parent->risk + risk;
    this->airDistance = std::sqrt((endX - x) * (endX - x) + (endY - y) * (endY - y));
    this->pathDistance = parent->pathDistance + 
        ((xChange != 0 && yChange != 0) ? std::sqrt(2) : 1);
    this->heuristic = this->risk * RISK_FACTOR + airDistance + pathDistance;
}

int* planPath(int width, int height, double* riskData, int maxRange, int startCoordX, int startCoordY, int endX, int endY) {
    //Lambda function to compare to candidates for the priority queue
    auto candidateComparer = [](Candidate *a, Candidate *b){return a->heuristic >= b->heuristic;};
    //The queue
    std::priority_queue<Candidate*, std::vector<Candidate*>, decltype(candidateComparer)> queue(candidateComparer);
    //The candidate with the starting coordinates
    Candidate* startCandidate = new Candidate(startCoordX, startCoordY, *(riskData + height * startCoordX + startCoordY), endX, endY);
    queue.push(startCandidate);
 
    //Lambda functions for hashing and equals methods for Candidates
    auto hash = [height](Candidate *candidate){return candidate->x * height + candidate->y;};
    auto equals = [](Candidate *a, Candidate *b){return a->x == b->x && a->y == b->y;};
    //Unordered set that checks if we've already visited a given candidate, to avoid visiting a single candidate many times
    std::unordered_set<Candidate*, decltype(hash), decltype(equals)> visitedCandidates(height * width, hash, equals);

    //While we're not at the end coordinates
    while(queue.top()->airDistance != 0) {
        //Grabs and pops the top of the queue
        Candidate* currentCandidate = queue.top();
        queue.pop();

        //Checks if we've visited this candidate before, and if so, if our current pathDistance is shorter. Second check is necessary for when our path has to be risk-heavy to avoid risk candidates further away being visited and written off already.
        if(visitedCandidates.count(currentCandidate) && (*visitedCandidates.find(currentCandidate))->pathDistance <= currentCandidate->pathDistance) {
            //No reason to visit candidate again, can drop it safely
            continue;
        } else {
            visitedCandidates.insert(currentCandidate);
        }

        //Checks the 8 surrounding squares and possible adds them as candidates
        for(int r = -1; r <= 1; ++r) {
            if(currentCandidate->y + r < 0 || currentCandidate->y + r >= height) {
                continue;
            }

            for(int c = -1; c <= 1; ++c) {
                if(r == 0 && c == 0) {
                    continue;
                }

                if(currentCandidate->x + c < 0 || currentCandidate->x + c >= width) {
                    continue;
                }

                //The square is a KOZ, can't go there at all
                if(*(riskData + height * (currentCandidate->x + c) + (currentCandidate->y + r)) >= 2) {
                    continue;
                }

                Candidate* nextCandidate = new Candidate(currentCandidate, c, r, *(riskData + height * (currentCandidate->x + c) + (currentCandidate->y + r)), endX, endY);

                //Makes sure the candidate is within range
                if(nextCandidate->pathDistance <= maxRange) {
                    //Adds it to the queue
                    queue.push(nextCandidate);
                }
            }
        }
    }

    std::vector<int> returnPath;
    Candidate* path = queue.top();
    int numCoords = 0;

    //Reverses through the path to get the path in order
    while(path != nullptr) {
        ++numCoords;
        returnPath.insert(std::begin(returnPath), path->y);
        returnPath.insert(std::begin(returnPath), path->x);
        path = path->parent;
    }

    //Inserts the size of the path so the .py file knows how far to iterate past the data pointer
    returnPath.insert(std::begin(returnPath), numCoords);

    //This is the... unsafe part. std::vector<int> deletes once the function scope ends, causing a segfault when the .py file tries to access the data pointer. So, instead, a dangling pointer is purposefully created to ensure the memory lives for an indeterminate time after the function scope ends so that the .py file can access the array via the data pointer.
    int* dangler = new int[returnPath.size()];

    for(int i = 0; i < returnPath.size(); ++i) {
        dangler[i] = returnPath[i];
    }

    return dangler;
}

extern "C" {
    int* planPath_c(int width, int height, double* riskData, int maxRange, int startCoordX, int startCoordY, int endX, int endY) {
        return planPath(width, height, riskData, maxRange, startCoordX, startCoordY, endX, endY);
    }
}
