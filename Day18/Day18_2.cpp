// Day 18 Part 2
// https://adventofcode.com/2022/day/18#part2

#include <iostream>
#include <bits/stdc++.h>

#define WORLD_SIZE 8

#define EMPTY 0
#define OCCUPIED 1
#define CHECKED 2

using namespace std;

void placeBlock(uint8_t (&world)[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE], vector<int> block) {
    world[block[0]][block[1]][block[2]] = OCCUPIED;
}


int main() {
    uint8_t world[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE] = {{{EMPTY}}};
    string rgxstr = "(\\d+),(\\d+),(\\d+)";
    int totalExposedArea = 0;
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

        placeBlock(world, {x+1, y+1, z+1}); //zero offset
    }

    // do BFS
    list<vector<int>> queue = {{0, 0, 0}};
    world[0][0][0] = CHECKED;

    while (queue.size() != 0) {
        std::cout << queue.size() << "  ";
        vector<int> cur = queue.front(); queue.pop_front();
        int x = cur[0]; int y = cur[1]; int z = cur[2];

        for (int dx : {-1, 1}) {
            if ((x+dx) >= 0 && (x+dx) < WORLD_SIZE && world[x+dx][y][z] == OCCUPIED) totalExposedArea++;
            if ((x+dx) >= 0 && (x+dx) < WORLD_SIZE && world[x+dx][y][z] == EMPTY) queue.push_back({x+dx, y, z}); world[x+dx][y][z] = CHECKED;
        }
        
        for (int dy : {-1, 1}) {
            if ((y+dy) >= 0 && (y+dy) < WORLD_SIZE && world[x][y+dy][z] == OCCUPIED) totalExposedArea++;
            if ((y+dy) >= 0 && (y+dy) < WORLD_SIZE && world[x][y+dy][z] == EMPTY) queue.push_back({x, y+dy, z}); world[x][y+dy][z] = CHECKED;
        }

        for (int dz : {-1, 1}) {
            if ((z+dz) >= 0 && (z+dz) < WORLD_SIZE && world[x][y][z+dz] == OCCUPIED) totalExposedArea++;
            if ((z+dz) >= 0 && (z+dz) < WORLD_SIZE && world[x][y][z+dz] == EMPTY) queue.push_back({x, y, z+dz}); world[x][y][z+dz] = CHECKED;
        }
    }

    std::cout << "Total exposed area: " << totalExposedArea << "\n";
    
    return 0;
}

// // calculate surface area
//     for (int x=0; x<WORLD_SIZE; x++) {
//         for (int y=0; y<WORLD_SIZE; y++) {
//             for (int z=0; z<WORLD_SIZE; z++) {
//                 if (!world[x][y][z]) {// check all empty spaces for adjacencies
//                     int adj = 0;
//                     for (int dx : {-1, 1}) {
//                         if ((x+dx) >= 0 && (x+dx) < WORLD_SIZE && world[x+dx][y][z]) adj++;
//                     }
                    
//                     for (int dy : {-1, 1}) {
//                         if ((y+dy) >= 0 && (y+dy) < WORLD_SIZE && world[x][y+dy][z]) adj++;
//                     }

//                     for (int dz : {-1, 1}) {
//                         if ((z+dz) >= 0 && (z+dz) < WORLD_SIZE && world[x][y][z+dz]) adj++;
//                     }
//                     totalExposedArea += adj % 6;
//                 }
//             }
//         }
//     }
