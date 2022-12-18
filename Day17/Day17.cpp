// Day 17
// https://adventofcode.com/2022/day/17

#include <iostream>
#include <bits/stdc++.h>
#include "wind.cpp"
#include "rocks.cpp"

using namespace std;

#define SIM_COUNT 2022

bool isInteference(bool (&chamber)[9000][7], Rock rock, int rockx, int rocky) {
    // checks if chamber intefers with the rock
    // assuming rock's 4*4 grid does not exceed the range of the chamber

    for (int x=0; x<rock.width; x++) {
        for (int y=0; y<rock.height; y++) {
            if (chamber[y+rocky][x+rockx] == true && rock.shape[y][x] == true) return true;
        }
    }
    return false;
}

void setInStone(bool (&chamber)[9000][7], Rock &rock, int rockx, int rocky) {
    for (int x=0; x<rock.width; x++) {
        for (int y=0; y<rock.height; y++) {
            if (rock.shape[y][x]) chamber[y+rocky][x+rockx] = true;
        }
    }
}

void dropStone(bool (&chamber)[9000][7], Rock &rock, int &x, int &y, int &windIdx) {
    while (true) {
            // wind
            char gust = wind[windIdx];

            if (gust == '>' && x+rock.width < 7) {
                bool intefere = isInteference(chamber, rock, x+1, y);
                if (!intefere) x++;
            } else if (gust == '<' && x > 0) {
                bool intefere = isInteference(chamber, rock, x-1, y);
                if (!intefere) x--;
            }
            windIdx++; if (windIdx == wind.length()) windIdx = 0;

            // drop
            if (y-1 < 0) goto set;
            bool intefere = isInteference(chamber, rock, x, y-1);
            if (intefere) {goto set;} else {y--;}
        }
        set:
        setInStone(chamber, rock, x, y);
}



int main() {
    bool chamber[9000][7] = {{0}};

    int windIdx = 0;

    int floor = 0;
    const int rockx = 2; int rocky = floor + 3;

    for (int n=0; n<SIM_COUNT; n++) {
        Rock rock = rocks[n % 5];
        int x = rockx; int y = rocky;

        dropStone(chamber, rock, x, y, windIdx);
        if (y+rock.height > floor) floor = y+rock.height;
        rocky = floor + 3;
    }

    std::cout << "Height: " << floor << "\n\n";
    return 0;
}
