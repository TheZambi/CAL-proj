#ifndef CAL_PROJ_BUSMANAGER_H
#define CAL_PROJ_BUSMANAGER_H

#include "Graph.h"
#include "Prisoner.h"

class BusManager {
    Graph<int> graph;
    Prisoner prisoner;
    int prisonLocation;

public:

    BusManager(const string &nodePath, const string &edgePath, int prisonLocation, Prisoner prisoner);
    vector<int> calcBusPath();

    vector<Vertex<int>*> getVertexSet();
    double getMinX();
    double getMinY();
    const Prisoner &getPrisoner() const;
    int getPrisonLocation() const;
private:
    void readGraphNodesFromFile(const string& path);
    void readGraphEdgesFromFile(const string& path);

};


#endif //CAL_PROJ_BUSMANAGER_H
