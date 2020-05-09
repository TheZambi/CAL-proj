#include "BusManager.h"
#include <fstream>
#include <sstream>

BusManager::BusManager(const string &nodePath, const string &edgePath, int prisonLocation, vector<Prisoner> &prisoners) : prisonLocation(prisonLocation) {

    this->graph = Graph<int>();
    this->prisoners = prisoners;

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
    int last_location = prisonLocation;

    //Prison to prisoner
    for(const auto & prisoner : prisoners){
        graph.dijkstraShortestPath(last_location);
        vector<int> pathToNext = graph.getPath(last_location, prisoner.getStart());
        result.insert(result.end(), pathToNext.begin(), pathToNext.end());

        //Prisoner path
        graph.dijkstraShortestPath(prisoner.getStart());
        vector<int> prisonerPath = graph.getPath(prisoner.getStart(), prisoner.getDestination());
        result.insert(result.end(), prisonerPath.begin(), prisonerPath.end());

        last_location = prisoner.getDestination();
    }

    return result;
}

int BusManager::getPrisonLocation() const {
    return prisonLocation;
}

const vector<Prisoner> &BusManager::getPrisoners() const {
    return this->prisoners;
}

