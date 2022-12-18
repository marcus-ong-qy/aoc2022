// Day 16
// https://adventofcode.com/2022/day/16

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// foundation of BFS codes obtained (and modified) from 
// https://www.geeksforgeeks.org/shortest-path-unweighted-graph/

class Valve {
    private:
        string name;
        int flowRate;

    public:
        map<string, int> adj; // distance to other valves

        Valve(const string name, const int flowRate) {
            this -> name = name;
            this -> flowRate = flowRate;
        }

        string getName() {return this -> name;}

        void setAdjacency(string name, int distance) {
            adj.insert_or_assign(name, distance);
        }
};

class ValveBFS {
    private:
        map<string, Valve> valves;
        map<string, vector<string>> connections;
        int bestPressureScore = 0; // Part 1 Answer

        list<Tracker> trackers;

        void bfs(string start) {
            list<string> queue;

            map<string, bool> visited; map<string, bool> dist;
            for (auto iter=connections.begin(); iter != connections.end(); iter++) {
                string vName = iter->first;
                visited.insert({vName, false}); dist.insert({vName, INT_MAX});
            }

            visited[start] = true; dist[start] = 0;
            queue.push_back(start);

            while (!queue.empty()) {
                string u = queue.front();
                queue.pop_front();
                for (int i = 0; i < connections[u].size(); i++) {
                    if (visited[connections[u][i]] == false) {
                        visited[connections[u][i]] = true;
                        dist[connections[u][i]] = dist[u] + 1;
                        queue.push_back(connections[u][i]);
                    }
                }
            }
            // assign adjacency values to each Valve object
            for (auto iter=dist.begin(); iter != dist.end(); iter++) {
                string vName = iter->first; int distance = iter->second;
                Valve valve = valves[vName];
                valve.setAdjacency(start, distance);
            }
        }

    public:
        void addValve(string name, int flowRate) {
            valves.insert_or_assign(name, new Valve(name, flowRate));
        }

        void addConnection(string v1name, string v2name) {
            if (connections.count(v1name) == 0) {
                vector<string> conn = {v2name};
                connections.insert({v1name, conn});
            } else {
                connections[v1name].push_back(v2name);
            }
        }

        void assignAdjacency() {
            for (auto iter=valves.begin(); iter != valves.end(); iter++) {
                string vName = iter->first; bfs(vName);
            }
        }

        

        // int findMaxPressure(string originame, int duration) {
        //     Valve originode = valves[originame];
        //     Tracker tracker = Tracker();

        //     return tracker.getMaxPressure(originode, 20);
        // }
};

class Tracker {
    private:
        Valve *currentValve;
        int steps;
        list<Tracker> *trackers;
        int *bestPressureScore;
        map<string, bool> visited;

        int stepInto(Valve valve, int stepsLeft) {
            Tracker newTracker = Tracker(valve, stepsLeft, *trackers, *bestPressureScore);
            trackers->push_back(newTracker);
        }

    public:
        Tracker(Valve &currentValve, int steps, 
            list<Tracker> &trackers, int &bestPressureScore) {
            this -> currentValve = &currentValve;
            this -> steps = steps;
            this -> trackers = &trackers;
            this -> bestPressureScore = &bestPressureScore;
        }

        int getMaxPressure() {
            // map<string, bool> visited;

            // TODO

            map<string, int> &adj = currentValve->adj;
            for (auto iter=adj.begin(); iter != adj.end(); iter++) {
                string vName = iter->first; int dist = iter->second;
            }

        }
};

int main() {
    string line;
    std::regex rgx = std::regex("^Valve ([A-Z]{2}) has flow rate=(\\d+); tunnels lead to valves ([A-Z]{2})(, [A-Z]{2})*$");
    std::smatch sm;
    ValveBFS simulation = ValveBFS();

    while (true) {
        getline(cin, line);
        if (line == "q!") break;
        std::regex_search(line, sm, rgx);

        string vName = sm[1]; int flowRate = stoi(sm[2]);

        simulation.addValve(vName, flowRate);
        for (int i=0; i<sm.length()-3; i++) {
            simulation.addConnection(vName, sm[i+3]);
        }
    }

    simulation.assignAdjacency();



    return 0;
}
