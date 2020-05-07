#ifndef CAL_PROJ_BUSMANAGER_H
#define CAL_PROJ_BUSMANAGER_H

#include "Graph.h"

class BusManager {
    Graph<int> graph;
public:
    BusManager(const string& nodePath, const string& edgePath);

    vector<Vertex<int>*> getVertexSet();
    double getMinX();
    double getMinY();
private:
    void readGraphNodesFromFile(const string& path);
    void readGraphEdgesFromFile(const string& path);

};


#endif //CAL_PROJ_BUSMANAGER_H
