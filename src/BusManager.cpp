#include "BusManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

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

class Compare
{
public:
    bool operator() (Vertex<int> *a, Vertex<int> *b)
    {
        if(a->getDist() >= b->getDist()) {
            return true;
        }
        return false;
    }
};

vector<int> BusManager::calcBusPath() {
    vector<int> result;
    int last_location = prisonLocation;
    priority_queue<Vertex<int>*, vector<Vertex<int>*>, Compare> queue;

    vector<Vertex<int>*> dests;
    make_heap(dests.begin(), dests.end(), Compare());

    for(const auto & prisoner : prisoners) {
        dests.push_back(graph.findVertex(prisoner.getStart()));
    }
    
    while(dests.size()) {
        vector<Vertex<int>*> temp;
        graph.dijkstraShortestPath(last_location);
        sort_heap(dests.begin(), dests.end());

        Vertex<int> *nextDest = dests.front();
        pop_heap(dests.begin(), dests.end());
        dests.pop_back();

        vector<int> pathToNext = graph.getPath(last_location, nextDest->getInfo());
        result.insert(result.end(), pathToNext.begin(), pathToNext.end());
        std::cout << last_location << endl;
        last_location = nextDest->getInfo();

        for(auto & prisoner : prisoners) {
            if (prisoner.getStart() == last_location) {
                prisoner.pickUp();
                dests.push_back(graph.findVertex(prisoner.getDestination()));
                push_heap(dests.begin(), dests.end());
            } else if (prisoner.getDestination() == last_location) {
                prisoner.deliver();
            }
        }
    }

    return result;
}

int BusManager::getPrisonLocation() const {
    return prisonLocation;
}

const vector<Prisoner> &BusManager::getPrisoners() const {
    return this->prisoners;
}

