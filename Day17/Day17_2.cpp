// Day 17 Part 2
// https://adventofcode.com/2022/day/17#part2

#include <iostream>
#include <bits/stdc++.h>
#include "wind.cpp"
#include "rocks.cpp"

using namespace std;

#define TRILLION 1000000000
#define CHAMBER_DEPTH 30000

bool isInteference(bool (&chamber)[CHAMBER_DEPTH][7], Rock rock, int rockx, int rocky) {
    // checks if chamber intefers with the rock
    // assuming rock's 4*4 grid does not exceed the range of the chamber

    for (int x=0; x<rock.width; x++) {
        for (int y=0; y<rock.height; y++) {
            if (chamber[y+rocky][x+rockx] == true && rock.shape[y][x] == true) return true;
        }
    }
    return false;
}

void setInStone(bool (&chamber)[CHAMBER_DEPTH][7], Rock &rock, int rockx, int rocky) {
    for (int x=0; x<rock.width; x++) {
        for (int y=0; y<rock.height; y++) {
            if (rock.shape[y][x]) chamber[y+rocky][x+rockx] = true;
        }
    }
}

void dropStone(bool (&chamber)[CHAMBER_DEPTH][7], Rock &rock, int &x, int &y, int &windIdx, int &windCycle) {
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
            windIdx++; 
            if (windIdx == wind.length()) {
                windIdx = 0;
                windCycle++;
            }

            // drop
            if (y-1 < 0) goto set;
            bool intefere = isInteference(chamber, rock, x, y-1);
            if (intefere) {goto set;} else {y--;}
        }
        set:
        setInStone(chamber, rock, x, y);
}

bool checkRepeated(bool (&chamber)[CHAMBER_DEPTH][7], int height) {
    return false;
}

void clearChamber(bool (&chamber)[CHAMBER_DEPTH][7]) {
    for (int y=0; y < CHAMBER_DEPTH; y++) {
        for (int x=0; x<7; x++) {
            chamber[y][x] = false;
        }
    }
}

int * getPeriod() {
    bool chamber[CHAMBER_DEPTH][7] = {{0}};
    bool chamberC1[CHAMBER_DEPTH][7] = {{0}};
    bool chamberC2[CHAMBER_DEPTH][7] = {{0}};

    int floor = 0;
    const int rockx = 2; int rocky = floor + 3;

    // values to find period
    // indicate end of period when rockIdx = 4, and windIdx = wind.length()

    int windIdx = 0; int windCycle = 0;
    int rockIdx = 0; // indicate which rock is falling

    // // height of a mini period i.e. when rockIdx and windIdx line up, but rock fall pattern may not repeat
    // // used for determining the true period by considering overlaps between miniperiods
    // // if miniPeriod != the period, check if miniPeriod*2 is the period, etc.
    vector<int> miniPeriods; 
    int mpcount = 0;

    long n = 0;
    while (true) {
        rockIdx = n % 5;
        Rock rock = rocks[rockIdx];
        int x = rockx; int y = rocky;

        dropStone(chamber, rock, x, y, windIdx, windCycle);

        if (y+rock.height > floor) floor = y+rock.height;
        rocky = floor + 3;
        n++;
        std::cout << n;

        if (windCycle == wind.length() && rockIdx == 4) {
            miniPeriods.push_back(n); mpcount++;
            if (mpcount % 2 == 0) {
                int half = miniPeriods[(mpcount/2)-1];
                if (n/2 == half) {
                    static int r[2] = {n, floor};
                    return r;
                }
            }
        }
    }

    // // print
    // for (int y=floor; y >= 0; y--) {
    //     for (int x=0; x<7; x++) {
    //         char val = chamber[y][x];
    //         if (val) {
    //             std::cout << '#';
    //         } else {
    //             std::cout << '.';
    //         }
    //     }
    //     std::cout << ' ' << y << '\n';
    // }
}

int main() {
    int *periodHeight = getPeriod();
    std:; cout << periodHeight[0] << "  " << periodHeight[1] << '\n';
}
