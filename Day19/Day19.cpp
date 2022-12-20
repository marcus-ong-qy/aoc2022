// Day 19
// https://adventofcode.com/2022/day/19

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Blueprint {
    private:
        bool buildOre() {
            if (ore >= oreRbtOreCost && (ore*obsRbtClayCost <= obsRbtOreCost*clay || ore*geodeRbtObsCost <= geodeRbtOreCost*obsidian)) {
                ore -= oreRbtOreCost; 
                return true;
            }
            return false;
        }
        bool buildClay() {
            if (ore >= clayRbtOreCost && (ore*obsRbtClayCost >= obsRbtOreCost*clay)) {
                ore -= clayRbtOreCost; 
                return true;
            }
            return false;
        }
        bool buildObsidian() {
            if (ore >= obsRbtOreCost && clay >= obsRbtClayCost) {
                ore -= obsRbtOreCost;   clay -= obsRbtClayCost; 
                return true;
            }
            return false;
        }
        bool buildGeode() {
            if (ore >= geodeRbtOreCost && obsidian >= geodeRbtObsCost) {
                ore -= geodeRbtOreCost;   obsidian -= geodeRbtObsCost; 
                return true;
            }
            return false;
        }

        void harvest() {
            ore += oreRobots;
            clay += clayRobots;
            obsidian += obsidianRobots;
            geode += geodeRobots;
        }
    public:
        int blueprintIdx; 
        int oreRbtOreCost;
        int clayRbtOreCost;
        int obsRbtOreCost;
        int obsRbtClayCost;
        int geodeRbtOreCost;
        int geodeRbtObsCost;

        int ore = 0; int oreRobots = 1;
        int clay = 0; int clayRobots = 0;
        int obsidian = 0; int obsidianRobots = 0;
        int geode = 0; int geodeRobots = 0;

    
        Blueprint(smatch sm) {
            this -> blueprintIdx    = stoi(sm[1]);
            this -> oreRbtOreCost   = stoi(sm[2]);
            this -> clayRbtOreCost  = stoi(sm[3]);
            this -> obsRbtOreCost   = stoi(sm[4]);
            this -> obsRbtClayCost  = stoi(sm[5]);
            this -> geodeRbtOreCost = stoi(sm[6]);
            this -> geodeRbtObsCost = stoi(sm[7]);
        }

        int getQualityLevel(int simLen) {
            for (int n=0; n<simLen; n++) {
                bool boughtGeode = buildGeode();
                bool boughtObsidian = buildObsidian();
                bool boughtClay = buildClay();
                bool boughtOre = buildOre();

                harvest();

                if (boughtGeode) geodeRobots++;
                if (boughtObsidian) obsidianRobots++;
                if (boughtClay) clayRobots++;
                if (boughtOre) oreRobots++;
                std::cout << "Minute " << n+1 << " -- " << "ore: " << ore << " - clay: " << clay << " - obsidian: " << obsidian << " - geode: " << geode;
                std::cout << " -- oreR: " << oreRobots << " - clayR: " << clayRobots << " - obsidianR: " << obsidianRobots << " - geodeR: " << geodeRobots << '\n';
            }
            return blueprintIdx * geode;
        }
};

int main() {
    string line;
    string rgxstr = "Blueprint (\\d+): Each ore robot costs (\\d+) ore. Each clay robot costs (\\d+) ore. Each obsidian robot costs (\\d+) ore and (\\d+) clay. Each geode robot costs (\\d+) ore and (\\d+) obsidian.";
    std::regex rgx = std::regex(rgxstr);
    std::smatch sm;

    vector<Blueprint> blueprints; int simLen = 24;

    int totalQuality = 0;

    // collect all blueprints
    while (true) {
        getline(cin, line);
        if (line == "q!") break;
        std::regex_search(line, sm, rgx);

        blueprints.push_back(Blueprint(sm));
    }

    for (Blueprint blueprint : blueprints) {
        int quality = blueprint.getQualityLevel(simLen);
        totalQuality += quality;
        std::cout << "Quality level: " << totalQuality << '\n'; 
    }

    std::cout << "Total Quality level: " << totalQuality << '\n'; 

    return 0;
}

// Blueprint 1: Each ore robot costs 4 ore. Each clay robot costs 2 ore. Each obsidian robot costs 3 ore and 14 clay. Each geode robot costs 2 ore and 7 obsidian.
// Blueprint 2: Each ore robot costs 2 ore. Each clay robot costs 3 ore. Each obsidian robot costs 3 ore and 8 clay. Each geode robot costs 3 ore and 12 obsidian.