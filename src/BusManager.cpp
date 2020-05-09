#include "BusManager.h"
#include <fstream>
#include <sstream>

BusManager::BusManager(const string &nodePath, const string &edgePath, int prisonLocation, Prisoner prisoner) : prisoner(prisoner), prisonLocation(prisonLocation) {

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

vector<int> BusManager::calcBusPath() {
    vector<int> result;
    //Prison to prisoner
    graph.dijkstraShortestPath(prisonLocation);
    result = graph.getPath(prisonLocation, prisoner.getStart());

    //Prisoner path
    graph.dijkstraShortestPath(prisoner.getStart());
    vector<int> prisionerPath = graph.getPath(prisoner.getStart(), prisoner.getDestination());
    result.insert(result.end(), prisionerPath.begin(), prisionerPath.end());

    return result;
}

int BusManager::getPrisonLocation() const {
    return prisonLocation;
}

const Prisoner &BusManager::getPrisoner() const {
    return prisoner;
}

