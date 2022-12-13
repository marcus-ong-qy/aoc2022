// Day 12 Part 2
// https://adventofcode.com/2022/day/12#part2

#include <iostream>
#include <bits/stdc++.h>
#include "./Day12.cpp"

// NOTE: algo is pretty highly inefficient
int main() {
    std::string line;
    std::vector<std::vector<Node>> map;
    std::vector<int> end;

    int rowIdx = 0;
    while (true) {
        std::cin >> line;
        if (line == "q!") break;

        std::vector<Node> nodes;

        for (int i=0; i < line.length(); i++) {
            char x = line[i];
            if (x == 'E')  end  = {i, rowIdx};
            nodes.push_back(Node(x, {i, rowIdx}));
        }

        map.push_back(nodes);
        rowIdx++;
    }

    std::vector<int> startTracker = map[end[1]][end[0]].getCoord();
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
                if (nextNode.getHeight() - curNode.getHeight() >= -1) {
                    if (!curNode.isPrevious(nextNode)) { // ensure no backtracking
                        if (nextNode.getHeight() == 'a') goto endloop; // 'a' found
                        std::vector<int> newTracker = nextNode.getCoord();
                        curNode.stepInto(nextNode);
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
    std::cout << "Shortest Distance from Nearest Origin: " << steps << std::endl;

    return 0;
}
