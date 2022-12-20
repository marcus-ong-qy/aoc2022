// Day 18
// https://adventofcode.com/2022/day/18

#include <iostream>
#include <bits/stdc++.h>

#define WORLD_SIZE 21

using namespace std;

int placeBlockAndGetAdjacency(bool (&world)[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE], vector<int> block) {
    int adj = 0;
    
    for (int dx : {-1, 1}) {
        if (world[block[0]+dx][block[1]][block[2]]) adj++;
    }
    
    for (int dy : {-1, 1}) {
        if (world[block[0]][block[1]+dy][block[2]]) adj++;
    }

    for (int dz : {-1, 1}) {
        if (world[block[0]][block[1]][block[2]+dz]) adj++;
    }

    world[block[0]][block[1]][block[2]] = true;

    return -(adj-3)*2;
}

int main() {
    bool world[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE] = {{{0}}};
    string rgxstr = "(\\d+),(\\d+),(\\d+)";
    int totalArea = 0;
    std::regex rgx = std::regex(rgxstr);
    std::smatch sm;
    
    while (true) {
        string line;
        std::cin >> line;
        if (line == "q!") break;

        std::regex_search(line, sm, rgx);

        int x=stoi(sm[1]);
        int y=stoi(sm[2]);
        int z=stoi(sm[3]);

        int darea = placeBlockAndGetAdjacency(world, {x+1, y+1, z+1}); //zero offset
        totalArea += darea;
    }

    std::cout << "Total area: " << totalArea << "\n";
    
    return 0;
}