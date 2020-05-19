#include "BusManager.h"
#include "Bus.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

BusManager::BusManager(const string &nodePath, const string &edgePath, const string &tagsPath, vector<Prisoner> &prisoners) {

    this->graph = Graph<int>();
    this->prisoners = prisoners;
    this->tags = {
            {"prison", {}},
            {"airport",{}},
            {"court",{}},
            {"train",{}},
            {"police", {}},
            {"hospital", {}}
    };

    this->buses = {};

    readGraphNodesFromFile(nodePath);
    readGraphEdgesFromFile(edgePath);
    readGraphTagsFromFile(tagsPath);
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

void BusManager::readGraphTagsFromFile(const string& path) {
    ifstream in(path);

    int id;
    string line, tag, name;

    if(in.is_open()){
        while(getline(in,line)){
            istringstream ss(line);
            ss >> id >> tag >> name;
            replace(name.begin(), name.end(), '_', ' ');
            if(tag == "prison")
                this->prisonLocation = id;
            this->tags.at(tag).push_back(std::pair<int, string>(id, name));

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

vector<vector<int>> BusManager::calcMultipleBusPath(int numBus)
{
    vector<vector<int>> results;
    bool emptyHeaps = false;
    buses.clear();
    buses = {new Bus(REGULAR,prisonLocation,1), new Bus(REGULAR,prisonLocation,3),
             new Bus(REGULAR,prisonLocation,2), new Bus(REGULAR,prisonLocation,1)};

    for(auto & buse : buses){
        vector<Vertex<int>*> dest;
        results.emplace_back();

        for(const auto & prisoner : prisoners) {
            dest.push_back(graph.findVertex(prisoner.getStart()));
        }
        buse->setDestinations(dest);
    }


    while(!emptyHeaps)
    {
        vector<Vertex<int>*> ignoredVertexes;

        for(int i = 0; i < buses.size() ; i++ ) {

            if (!buses.at(i)->getDestinations().empty()) {
                bool hadAction = false;
                vector<Vertex<int> *> temp;

                graph.dijkstraShortestPath(buses.at(i)->getLastLocation());
                buses.at(i)->startHeap();

                Vertex<int> *nextDest = buses.at(i)->popHeap();

                vector<int> pathToNext = graph.getPath(buses.at(i)->getLastLocation(), nextDest->getInfo());

                int currentLocation = buses.at(i)->getLastLocation();
                buses.at(i)->setLastLocation(nextDest->getInfo());

                for (auto &prisoner : prisoners) {
                    if (prisoner.getStart() == buses.at(i)->getLastLocation() && !prisoner.isPickedUp()) {
                        int currentBusToNextDestDist = nextDest->getDist();
                        for(size_t j = 0; j < buses.size(); j++ ) {
                            graph.dijkstraShortestPath(buses.at(j)->getLastLocation());
                            int nextDist = nextDest->getDist();
                            bool ignore = false;
                            for(auto &prisoner1 : prisoners) {
                                if(i != j && prisoner1.isPickedUp() && !prisoner1.isDelivered() && prisoner1.getBusNum() == j) {
                                    graph.dijkstraShortestPath(prisoner1.getDestination());
                                    if(nextDest->getDist() < nextDist) {
                                        ignoredVertexes.push_back(nextDest);
                                        ignore = true;
                                        break;
                                    }
                                }
                            }
                            if(ignore)
                                break;
                            if(i!=j && currentBusToNextDestDist > nextDist) {
                                ignoredVertexes.push_back(nextDest);
                                break;
                            }
                            else if(j==buses.size()-1) {
                                if(buses.at(i)->canFit(prisoner)){
                                    buses.at(i)->addCurrentCapacity(prisoner.getWeight());
                                    prisoner.pickUp(i);
                                    buses.at(i)->addDest(graph.findVertex(prisoner.getDestination()));
                                    hadAction = true;
                                } else
                                    ignoredVertexes.push_back(nextDest);
                            }
                        }
                    } else if (prisoner.getDestination() == buses.at(i)->getLastLocation() && prisoner.isPickedUp() &&
                               prisoner.getBusNum() == i) {
                        prisoner.deliver();
                        buses.at(i)->addCurrentCapacity(prisoner.getWeight()*-1);
                        hadAction=true;
                    }
                }

                bool aux = buses.at(i)->getDestinations().empty();
                if(hadAction || aux) {
                    if (!hadAction) {
                        buses.at(i)->setLastLocation(currentLocation);
                    }
                    for (auto &ignoredVertex : ignoredVertexes)
                        buses.at(i)->addDest(ignoredVertex);
                    ignoredVertexes.clear();
                }
                else{
                    buses.at(i)->setLastLocation(currentLocation);
                    i--;
                }
                
                if(hadAction){
                    if(results[i].empty())
                        results[i].insert(results[i].end(), pathToNext.begin(), pathToNext.end());
                    else
                        results[i].insert(results[i].end(), next(pathToNext.begin(),1), pathToNext.end());
                }
            }

        }

        for(size_t i = 0 ; i < buses.size() ; i++)
        {
            if(!buses.at(i)->getDestinations().empty())
                break;
            if(i==buses.size()-1)
                emptyHeaps=true;
        }


    }

    for(int i = 0; i < buses.size(); ++i) {
        graph.dijkstraShortestPath(buses.at(i)->getLastLocation());
        vector<int> pathToPrison = graph.getPath(buses.at(i)->getLastLocation(), prisonLocation);
        results[i].insert(results[i].end(), next(pathToPrison.begin(),1), pathToPrison.end());
    }

    //Eliminar os autocarros que não foram usados e adiciona os sítios com tag visitados pelo autocarros
    for(int i = results.size() - 1; i >= 0; i--) {
        if(results.at(i).size() <= 1) {
            buses.erase(buses.begin() + i);
        }
        else {
            //int oldRes = -1;
            for(int res : results.at(i)) {
                //if(res != oldRes) {
                    for (pair<int, string> tv : this->getTags()) {
                        if (tv.first == res) {
                            buses.at(i)->addVisited(tv);
                            break;
                        }
                    }
                    //oldRes = res;
                //}
            }
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

vector<pair<int, string>> BusManager::getTags() {
    vector<pair<int, string>> aux;
    for(auto t : tags) {
        aux.insert(aux.end(), t.second.begin(), t.second.end());
    }
    return aux;
}

vector<Bus *> BusManager::getBuses() {
    return buses;
}

