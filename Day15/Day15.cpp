// Day 15
// https://adventofcode.com/2022/day/15

#include <iostream>
#include <bits/stdc++.h>

#define MILLION 1000000
#define INSPECT_Y 2*MILLION
#define X_OFFSET 10*MILLION

int main() {
    std::string line;

    std::regex rgx = std::regex("^Sensor at x=(-?\\d+), y=(-?\\d+): closest beacon is at x=(-?\\d+), y=(-?\\d+)$");
    std::smatch sm;

    std::vector<int> yRow(2*X_OFFSET);

    while (true) {
        std::getline(std::cin, line);
        if (line == "q!") break;

        std::regex_search(line, sm, rgx);

        int sx = stoi(sm[1]); int sy = stoi(sm[2]);
        int bx = stoi(sm[3]); int by = stoi(sm[4]);

        int diamSize = abs(sx-bx) + abs(sy-by);

        if (abs(INSPECT_Y - sy) <= diamSize) {
            int covSizeAtRow = diamSize - abs(INSPECT_Y - sy);
            for (int x=sx-covSizeAtRow; x<=sx+covSizeAtRow; x++) {
                yRow[x+X_OFFSET] = 1;
            }
        }
        if(by == INSPECT_Y) yRow[bx+X_OFFSET] = 0;
    }

    int noBeaconCount = 0;
    for (int i=0; i<2*X_OFFSET; i++) {
        noBeaconCount += yRow[i];
    }

    std::cout << "Positions with no Beacon: " << noBeaconCount << "\n"; 

    return 0;
}
