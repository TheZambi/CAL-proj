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
    double w;
    string line;

    if(in.is_open()){
        getline(in,line);
        count = stoi(line);

        for(size_t i = 0; i < count; ++i){
            getline(in,line);
            istringstream ss(line);
            ss >> c >> id1 >> c >> id2 >> c >> w;

            this->graph.addEdge(id1,id2,w);

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
        return a->getDist() > b->getDist();
    }
};

vector<vector<int>> BusManager::calcMultipleBusPath(int numBus)
{
    vector<vector<int>> results;
    vector<int> last_locations;
    bool emptyHeaps = false;

    vector<vector<Vertex<int>*>> dests;



    for(size_t i = 0 ;i<numBus ; i++){
        results.emplace_back();
        last_locations.push_back(prisonLocation);
        dests.emplace_back();

        for(const auto & prisoner : prisoners) {
            dests[i].push_back(graph.findVertex(prisoner.getStart()));
        }

        make_heap(dests.at(i).begin(), dests.at(i).end(), Compare());

    }

    while(!emptyHeaps)
    {
        size_t i=0;
        vector<Vertex<int>*> ignoredVertexes;
        for(i = 0; i < numBus ; i++ ) {
            if (!dests[i].empty()) {
                bool hadAction = false;
                vector<Vertex<int> *> temp;

                graph.dijkstraShortestPath(last_locations[i]);
                make_heap(dests.at(i).begin(), dests.at(i).end(), Compare());

                Vertex<int> *nextDest = dests[i].front();
                pop_heap(dests[i].begin(), dests[i].end());
                dests[i].pop_back();

                vector<int> pathToNext = graph.getPath(last_locations[i], nextDest->getInfo());

                int currentLocation = last_locations[i];
                last_locations[i] = nextDest->getInfo();

                for (auto &prisoner : prisoners) {
                    if (prisoner.getStart() == last_locations[i] && !prisoner.isPickedUp()) {
                        int currentBusToNextDestDist = nextDest->getDist();
                        for(size_t j = 0; j < numBus; j++ ) {
                            graph.dijkstraShortestPath(last_locations[j]);
                            if(i!=j && currentBusToNextDestDist > nextDest->getDist()) {
                                ignoredVertexes.push_back(nextDest);
                                break;
                            }
                            else if(j==numBus-1) {
                                prisoner.pickUp(i);
                                dests[i].push_back(graph.findVertex(prisoner.getDestination()));
                                hadAction = true;
                            }
                        }
                    } else if (prisoner.getDestination() == last_locations[i] && prisoner.isPickedUp() &&
                               prisoner.getBusNum() == i) {
                        prisoner.deliver();
                        hadAction=true;
                    }
                }
                if(!hadAction) {
                    last_locations[i] = currentLocation;
                    i--;
                } else{
                    results[i].insert(results[i].end(), pathToNext.begin(), pathToNext.end());
                }

                if(hadAction || dests[i].empty())
                {
                    for(size_t k=0;k<ignoredVertexes.size();k++)
                        dests[i].push_back(ignoredVertexes[k]);
                }
            }

        }




        for(size_t i = 0 ; i < numBus ; i++)
        {
            if(!dests[i].empty())
                break;
            if(i==numBus-1)
                emptyHeaps=true;
        }
    }
    return results;
}

vector<int> BusManager::calcBusPath() {
    vector<int> result;
    int last_location = prisonLocation;

    vector<Vertex<int>*> dests;
    make_heap(dests.begin(), dests.end(), Compare());

    for(const auto & prisoner : prisoners) {
        dests.push_back(graph.findVertex(prisoner.getStart()));
    }
    
    while(!dests.empty()) {
        vector<Vertex<int>*> temp;
        graph.dijkstraShortestPath(last_location);
        sort_heap(dests.begin(), dests.end());

        Vertex<int> *nextDest = dests.front();
        pop_heap(dests.begin(), dests.end());
        dests.pop_back();

        vector<int> pathToNext = graph.getPath(last_location, nextDest->getInfo());
        result.insert(result.end(), pathToNext.begin(), pathToNext.end());
        last_location = nextDest->getInfo();

        for(auto & prisoner : prisoners) {
            if (prisoner.getStart() == last_location && !prisoner.isPickedUp()) {
                prisoner.pickUp(0);
                dests.push_back(graph.findVertex(prisoner.getDestination()));
                push_heap(dests.begin(), dests.end());
            } else if (prisoner.getDestination() == last_location && prisoner.isDelivered()) {
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

bool BusManager::addPrisoner(Prisoner prisoner) {
    for(Prisoner prisoner1 : prisoners) {
        if(prisoner1.getStart() == prisoner.getStart() &&
        prisoner1.getDestination() == prisoner.getDestination())
            return false;
    }
    this->prisoners.push_back(prisoner);
    return true;
}

void BusManager::resetPrisoners() {
    this->prisoners = {};
}

