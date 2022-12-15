// Day 15 Part 2
// https://adventofcode.com/2022/day/15#part2

#include <iostream>
#include <bits/stdc++.h>

#define MILLION 1000000
#define SEARCH_AREA_SPAN 4*MILLION

bool inRange(int& sampx, int& sampy, int& sensorx, int& sensory, int& sensorsize) {
    int dist = abs(sensorx-sampx) + abs(sensory-sampy);
    return dist <= sensorsize;
}

std::vector<std::vector<int>> paramPoints(int& sx, int& sy, int& ssize) {
    std::vector<std::vector<int>> paramPoints;

    for (int dy=0; dy<=ssize+1; dy++) {
        int dx = ssize-dy+1;
        paramPoints.push_back({sx+dx, sy+dy});
        paramPoints.push_back({sx-dx, sy+dy});
        paramPoints.push_back({sx+dx, sy-dy});
        paramPoints.push_back({sx-dx, sy-dy});
    }
    return paramPoints;
}

int main() {
    std::string line;

    std::regex rgx = std::regex("^Sensor at x=(-?\\d+), y=(-?\\d+): closest beacon is at x=(-?\\d+), y=(-?\\d+)$");
    std::smatch sm;

    std::vector<std::vector<int>> sensors; 
    std::vector<std::vector<int>> possiblePoints;

    while (true) {
        std::getline(std::cin, line);
        if (line == "q!") break;

        std::regex_search(line, sm, rgx);

        int sx = stoi(sm[1]); int sy = stoi(sm[2]);
        int bx = stoi(sm[3]); int by = stoi(sm[4]);

        int diamSize = abs(sx-bx) + abs(sy-by);
        
        sensors.push_back({sx, sy, diamSize});

        std::vector<std::vector<int>> pPoints = paramPoints(sx, sy, diamSize);
        for (std::vector<int> point : pPoints) {
            if (0 <= point[0] && point[0] <= SEARCH_AREA_SPAN && 
                0 <= point[1] && point[1] <= SEARCH_AREA_SPAN) possiblePoints.push_back(point);
        }
    }

    for (std::vector<int> point : possiblePoints) {
        int x = point[0]; int y = point[1];
        bool eureka = true;
        for (std::vector<int> sensor : sensors) {
            bool isInRange = inRange(x, y, sensor[0], sensor[1], sensor[2]);
            if (isInRange) {
                eureka = false; goto next;
            }
        }
        if (eureka) {
            std::cout << "Beacon Found at: x=" << x << ", y=" << y << " (!!)\n";
            std::cout << "Frequency: " << (long) x*(4*MILLION) + y << "\n";
            return 0;
        }
        next: {}
    }

    std::cout << "No Location Found" << "\n"; 
    return 1;
}
