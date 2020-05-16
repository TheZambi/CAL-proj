#ifndef CAL_PROJ_BUSMANAGER_H
#define CAL_PROJ_BUSMANAGER_H

#include "Graph.h"
#include "Prisoner.h"
#include <map>

class BusManager {
    Graph<int> graph;
    vector<Prisoner> prisoners;
    int prisonLocation;
    map<string,vector<int>> tags;

public:

    BusManager(const string &nodePath, const string &edgePath,const string &tagPath, vector<Prisoner> &prisoners);
    vector<int> calcBusPath();

    vector<Vertex<int>*> getVertexSet();
    double getMinX();
    double getMinY();
    const vector<Prisoner> &getPrisoners() const;
    int getPrisonLocation() const;
    vector<vector<int>> calcMultipleBusPath(int numBus);
    void addPrisoner(Prisoner prisoner);

private:
    void readGraphNodesFromFile(const string& path);
    void readGraphEdgesFromFile(const string& path);

    void readGraphTagsFromFile(const string &basicString);
};


#endif //CAL_PROJ_BUSMANAGER_H
