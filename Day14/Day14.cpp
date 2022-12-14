// Day 14
// https://adventofcode.com/2022/day/14

#include <iostream>
#include <bits/stdc++.h>


int main() {
    std::string line;
    int map[500][1000] = {{0}};

    std::string delimiter = " -> ";
    // draw walls
    while (true) {
        std::getline(std::cin, line);
        if (line == "q!") break;

        std::vector<std::vector<int>> walls;
        while(line.length() > 0) {
            std::string point = line.substr(0, line.find(delimiter));
            int x = stoi(point.substr(0, line.find(',')));
            int y = stoi(point.substr(line.find(',')+1, point.length()));
            walls.push_back({x, y});
            line.erase(0, point.length() + delimiter.length());
        }

        // draw walls
        for (int i=0; i<walls.size()-1; i++) {
            std::vector<int> point1 = walls[i];
            std::vector<int> point2 = walls[i+1];

            if (point1[0] == point2[0]) {// vertical wall
                int x = point1[0];
                int miny = std::min(point1[1], point2[1]);
                int maxy = std::max(point1[1], point2[1]);
                for (int y=miny; y<=maxy; y++) map[y][x] = 1;
            } else if (point1[1] == point2[1]) {// horizontal wall
                int y = point1[1];
                int minx = std::min(point1[0], point2[0]);
                int maxx = std::max(point1[0], point2[0]);
                for (int x=minx; x<=maxx; x++) map[y][x] = 1;
            }
        }
    }

    // drop the sand
    int sandCount = 0;
    while (true) {
        int x = 500; int y = 0;
        bool atRest = false;
        while (!atRest) {
            if (y == 499) {// void
                goto end;
            } else if (map[y+1][x] == 0) {// bottom
                y++;
            } else if (map[y+1][x-1] == 0) {// left
                y++; x--;
            } else if (map[y+1][x+1] == 0) {// right
                y++; x++;
            } else {// at rest
                atRest = true;
                map[y][x] = 1;
                sandCount++;
            }
        }
    }

    end:
    std::cout << "Sand Count: " << sandCount << std::endl;

    return 0;
}
