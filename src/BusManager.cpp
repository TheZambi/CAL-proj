#include "BusManager.h"
#include <fstream>
#include <sstream>

BusManager::BusManager(const string& nodePath, const string& edgePath){

    this->graph = Graph<int>();

    readGraphNodesFromFile(nodePath);
    readGraphEdgesFromFile(edgePath);
}

void BusManager::readGraphNodesFromFile(const string& path){

    ifstream in(path);

    double minX = INF;
    double minY = INF;

    int count;
    char c;
    double x,y;
    int id;
    string line;

    if(in.is_open()){
        getline(in,line);
        count = stoi(line);

        for(size_t i = 0; i < count; ++i){
            getline(in,line);
            istringstream ss(line);
            ss >> c >> id >> c >> x >> c >> y;

            this->graph.addVertex(id,x,y);

            minX = min(minX, x);
            minY = min(minY, y);
        }

        this->graph.setMinX(minX);
        this->graph.setMinY(minY);
    }

    in.close();
}

void BusManager::readGraphEdgesFromFile(const string& path){

    ifstream in(path);

    int count;
    char c;
    int id1,id2;
    string line;

    if(in.is_open()){
        getline(in,line);
        count = stoi(line);

        for(size_t i = 0; i < count; ++i){
            getline(in,line);
            istringstream ss(line);
            ss >> c >> id1 >> c >> id2 >> c;

            this->graph.addEdge(id1,id2,graph.calculateVertexDistance(id2,id1));

        }
    }

    in.close();
}

vector<Vertex<int>*> BusManager::getVertexSet(){
    return this->graph.getVertexSet();
}


double BusManager::getMinX() {
    return this->graph.getMinX();
}

double BusManager::getMinY() {
    return this->graph.getMinY();
}
