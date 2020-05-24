#ifndef CAL_PROJ_BUSMANAGER_H
#define CAL_PROJ_BUSMANAGER_H

#include "Graph.h"
#include "Prisoner.h"
#include "Bus.h"
#include <map>

class BusManager {
    Graph<int> graph;
    vector<Prisoner> prisoners;
    int prisonLocation;
    map<string,vector<pair<int, string>>> tags;
    vector<Bus*> buses;


public:

    BusManager(const string &nodePath, const string &edgePath,const string &tagPath);
    vector<int> calcBusPath();

    vector<Vertex<int>*> getVertexSet();
    double getMinX();
    double getMinY();
    const vector<Prisoner> &getPrisoners() const;
    int getPrisonLocation() const;
    vector<vector<int>> calcMultipleBusPath();
    bool addPrisoner(Prisoner prisoner);
    void addBus(Bus *bus);
    void resetPrisoners();
    void resetBuses();
    vector<pair<int, string>> getTags();
    vector<Bus*> getBuses();
    void readData();
    void reset();

private:
    void readGraphNodesFromFile(const string& path);
    void readGraphEdgesFromFile(const string& path);
    void readGraphTagsFromFile(const string &basicString);
    bool hasPath(Prisoner prisoner);


};


#endif //CAL_PROJ_BUSMANAGER_H
