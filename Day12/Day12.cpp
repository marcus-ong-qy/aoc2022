// Day 12
// https://adventofcode.com/2022/day/12

#include <iostream>
#include <bits/stdc++.h>

class Node {
    private:
        int height;
        std::vector<int> coord;
        std::vector<int> prevCoord = {-1, -1};


        void setPrevCoord(std::vector<int> prevCoord) {
            this -> prevCoord = prevCoord;
        }

    public:
        Node(char htC, std::vector<int> coord) {
                 if (htC == 'S') this -> height = 'a';
            else if (htC == 'E') this -> height = 'z';
            else                 this -> height = htC;
            this -> coord = coord;
        }

        void stepInto(Node nextNode) {
            nextNode.setPrevCoord(this -> coord);
        }

        int getHeight() {return height;}

        std::vector<int> getCoord() {return coord;}

        std::vector<int> getPrevCoord() {return prevCoord;};

        bool isPrevious(Node nextNode) {
            return (nextNode.getCoord()[0] == prevCoord[0] && 
                    nextNode.getCoord()[1] == prevCoord[0]);
        }
};

// NOTE: algo is pretty highly inefficient
int main() {
    std::string line;
    std::vector<std::vector<Node>> map;
    std::vector<int> start;
    std::vector<int> end;

    int rowIdx = 0;
    while (true) {
        std::cin >> line;
        if (line == "q!") break;

        std::vector<Node> nodes;

        for (int i=0; i < line.length(); i++) {
            char x = line[i];
                 if (x == 'S') start = {i, rowIdx};
            else if (x == 'E')  end  = {i, rowIdx};
            nodes.push_back(Node(x, {i, rowIdx}));
        }

        map.push_back(nodes);
        rowIdx++;
    }

    std::vector<int> startTracker = map[start[1]][start[0]].getCoord();
    std::vector<std::vector<int>> trackers = {startTracker};
    std::vector<std::vector<int>>::iterator itr;

    int steps = 0;

     while (trackers.size() > 0) {
        steps++;
        std::vector<std::vector<int>> newTrackers;

        for (itr = trackers.begin(); itr != trackers.end(); itr++) {
            std::vector<int> curTracker = *itr;
            Node curNode = map[curTracker[1]][curTracker[0]];
            std::vector<Node> nextNodes; // up, down, left, right of curNode
            if (curTracker[1]-1 >= 0)            nextNodes.push_back(map[curTracker[1]-1][curTracker[0]]  );
            if (curTracker[1]+1 < map.size())    nextNodes.push_back(map[curTracker[1]+1][curTracker[0]]  );
            if (curTracker[0]-1 >= 0)            nextNodes.push_back(map[curTracker[1]]  [curTracker[0]-1]);
            if (curTracker[0]+1 < map[0].size()) nextNodes.push_back(map[curTracker[1]]  [curTracker[0]+1]);

            std::vector<Node>::iterator nextNodeItr;
            for (nextNodeItr = nextNodes.begin(); nextNodeItr != nextNodes.end(); nextNodeItr++) {
                Node nextNode = *nextNodeItr;
                if (nextNode.getHeight() - curNode.getHeight() <= 1) {
                    if (!curNode.isPrevious(nextNode)) { // ensure no backtracking
                        std::vector<int> newTracker = nextNode.getCoord();
                        curNode.stepInto(nextNode);
                        if (newTracker[0] == end[0] && newTracker[1] == end[1]) {
                            goto endloop; // endpoint found
                        }
                        newTrackers.push_back(newTracker);
                    }
                }
            }
        }

        trackers = {}; // reset and replace old trackers with newTrackers
        std::vector<std::vector<int>>::iterator itrNew;

        std::cout << "Step: " << steps << std::endl;
        for (itrNew = newTrackers.begin(); itrNew != newTrackers.end(); itrNew++) {
            bool isUnique = true; // ensure no duplicates in trackers
            for (itr = trackers.begin(); itr != trackers.end(); itr++) {
                std::vector<int> trk = *itr; std::vector<int> newTrk = *itrNew;
                if (trk[0] == newTrk[0] && trk[1] == newTrk[1]) {isUnique = false;}
            }
            if (isUnique) {
                trackers.push_back(*itrNew);
            }
        }
    }
    // if trackers.size() == 0
    std::cout << "No Paths Found!" << std::endl; return 1;

    endloop:
    std::cout << "Shortest Distance: " << steps << std::endl;

    return 0;
}
