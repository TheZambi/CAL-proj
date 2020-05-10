#include "BusManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

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

    graph.dijkstraShortestPath(last_location);
    for(const auto & prisoner : prisoners) {
        if(prisoner.isPickedUp()) {
            queue.push(graph.findVertex(prisoner.getDestination()));
        } else if(!prisoner.isDelivered()) {
            queue.push(graph.findVertex(prisoner.getStart()));
        }
    }

    //Prison to prisoner
    while(!queue.empty()) {
        vector<Vertex<int>*> temp;
        while(!queue.empty()) {
            temp.push_back(queue.top());
            queue.pop();
        }
        for(int i = 0; i < temp.size(); ++i) {
            queue.push(temp.at(i));
        }
        graph.dijkstraShortestPath(last_location);
        Vertex<int> *nextDest = queue.top();
        queue.pop();
        vector<int> pathToNext = graph.getPath(last_location, nextDest->getInfo());
        result.insert(result.end(), pathToNext.begin(), pathToNext.end());
        std::cout << last_location << endl;
        last_location = nextDest->getInfo();

        for(auto & prisoner : prisoners) {
            if (prisoner.getStart() == last_location) {
                prisoner.pickUp();
                queue.push(graph.findVertex(prisoner.getDestination()));
            } else if (prisoner.getDestination() == last_location) {
                prisoner.deliver();
            }
        }
    }

//    for(const auto & prisoner : prisoners){
//        graph.dijkstraShortestPath(last_location);
//        vector<int> pathToNext = graph.getPath(last_location, prisoner.getStart());
//        result.insert(result.end(), pathToNext.begin(), pathToNext.end());
//
//        //Prisoner path
//        graph.dijkstraShortestPath(prisoner.getStart());
//        vector<int> prisonerPath = graph.getPath(prisoner.getStart(), prisoner.getDestination());
//        result.insert(result.end(), prisonerPath.begin(), prisonerPath.end());
//
//        last_location = prisoner.getDestination();
//    }

    return result;
}

int BusManager::getPrisonLocation() const {
    return prisonLocation;
}

const vector<Prisoner> &BusManager::getPrisoners() const {
    return this->prisoners;
}

