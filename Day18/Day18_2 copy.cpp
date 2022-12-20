// Day 18 Part 2
// https://adventofcode.com/2022/day/18#part2

#include <iostream>
#include <bits/stdc++.h>

#define WORLD_SIZE 21

using namespace std;

void placeBlock(int (&world)[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE], vector<int> block) {
    world[block[0]][block[1]][block[2]] = 1;
}

int placeBlockAndGetAdjacency(int (&world)[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE], vector<int> block) {
    int adj = 0;
    
    for (int dx : {-1, 1}) {
        if (world[block[0]+dx][block[1]][block[2]] == 1) adj++;
    }
    
    for (int dy : {-1, 1}) {
        if (world[block[0]][block[1]+dy][block[2]] == 1) adj++;
    }

    for (int dz : {-1, 1}) {
        if (world[block[0]][block[1]][block[2]+dz] == 1) adj++;
    }

    world[block[0]][block[1]][block[2]] = 1;

    return -(adj-3)*2;
}

// helper function for fillOuterAir
void fillAir(int (&world)[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE], int x, int y, int z) {
        if (world[x][y][z] == 0) {

            for (int dx : {-1, 1}) {
                if ((x+dx) >= 0 && (x+dx) < WORLD_SIZE) {
                    if (world[x+dx][y][z] == 2) {
                        goto next; world[x][y][z] = 2;
                    }
                }
            }

            for (int dy : {-1, 1}) {
                if ((x+dy) >= 0 && (x+dy) < WORLD_SIZE) {
                    if (world[x][y+dy][z] == 2) {
                        goto next; world[x][y][z] = 2;
                    }
                }
            }

            for (int dz : {-1, 1}) {
                if ((x+dz) >= 0 && (x+dz) < WORLD_SIZE) {
                    if (world[x][y][z+dz] == 2) {
                        goto next; world[x][y][z] = 2;
                    }
                }
            }

        }
        next: {}
    }

void fillOuterAir(int (&world)[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE]) {
    world[0][0][0] = 2;

    for (int z=0; z<WORLD_SIZE; z++) {
        for (int y=0; y<WORLD_SIZE; y++) {
            for (int x=0; x<WORLD_SIZE; x++) {
                fillAir(world, x, y, z);
            }
        }
    }

    for (int z=WORLD_SIZE-1; z>=0; z--) {
        for (int y=WORLD_SIZE-1; y>=0; y--) {
            for (int x=WORLD_SIZE-1; x>=0; x--) {
                fillAir(world, x, y, z);
            }
        }
    }

        for (int y=0; y<WORLD_SIZE; y++) {
    for (int z=0; z<WORLD_SIZE; z++) {
            for (int x=0; x<WORLD_SIZE; x++) {
                fillAir(world, x, y, z);
            }
        }
    }

        for (int y=WORLD_SIZE-1; y>=0; y--) {
    for (int z=WORLD_SIZE-1; z>=0; z--) {
            for (int x=WORLD_SIZE-1; x>=0; x--) {
                fillAir(world, x, y, z);
            }
        }
    }

    for (int z=0; z<WORLD_SIZE; z++) {
            for (int x=0; x<WORLD_SIZE; x++) {
        for (int y=0; y<WORLD_SIZE; y++) {
                fillAir(world, x, y, z);
            }
        }
    }

    for (int z=WORLD_SIZE-1; z>=0; z--) {
            for (int x=WORLD_SIZE-1; x>=0; x--) {
        for (int y=WORLD_SIZE-1; y>=0; y--) {
                fillAir(world, x, y, z);
            }
        }
    }
}

int findPocketSurfaceArea(int (&world)[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE], vector<int> start) {
    int x = start[0]; int y = start[1]; int z = start[2];
    world[x][y][z] = 2;

    int adj_surfaces = 0;

    for (int dx : {-1, 1}) {
        if ((x+dx) >= 0 && (x+dx) < WORLD_SIZE) {
            if (world[x+dx][y][z] == 1) {
                adj_surfaces++;
            } else if (world[x+dx][y][z] == 0) {
                adj_surfaces += findPocketSurfaceArea(world, {x+dx, y, z});
            }
        }
    }

    for (int dy : {-1, 1}) {
        if ((y+dy) >= 0 && (y+dy) < WORLD_SIZE) {
            if (world[x][y+dy][z] == 1) {
                adj_surfaces++;
            } else if (world[x][y+dy][z] == 0) {
                adj_surfaces += findPocketSurfaceArea(world, {x, y+dy, z});
            }
        }
    }

    for (int dz : {-1, 1}) {
        if ((z+dz) >= 0 && (z+dz) < WORLD_SIZE) {
            if (world[x][y][z+dz] == 1) {
                adj_surfaces++;
            } else if (world[x][y][z+dz] == 0) {
                adj_surfaces += findPocketSurfaceArea(world, {x, y, z+dz});
            }
        }
    }

    return adj_surfaces;
}

int main() {
    int world[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE] = {{{0}}}; // 0: air, 1: occupied, 2: checked air
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

        int darea = placeBlockAndGetAdjacency(world, {x+1, y+1, z+1}); //zero offset
        totalExposedArea += darea;
        // placeBlock(world, {x+1, y+1, z+1}); //zero offset
    }

    // // detect outer air 'pocket'
    // int totalExposedArea = findPocketSurfaceArea(world, {0, 0, 0});

    // fill up outer air 'pocket' with 2s
    fillOuterAir(world);
    std::cout << "outer air is filled\n";

    for (int z=0; z<WORLD_SIZE; z++) {
        for (int y=0; y<WORLD_SIZE; y++) {
            for (int x=0; x<WORLD_SIZE; x++) {
                if (world[x][y][z] == 0) std::cout << "F";
            }
        }
    }

    

    // detect inner air pockets
    for (int z=0; z<WORLD_SIZE; z++) {
        for (int y=0; y<WORLD_SIZE; y++) {
            for (int x=0; x<WORLD_SIZE; x++) {
                if (world[x][y][z] == 0) {
                    std::cout << "oyo";
                    totalExposedArea -= findPocketSurfaceArea(world, {x, y, z});
                }
            }
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
