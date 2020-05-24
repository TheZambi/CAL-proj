#include "BusManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

BusManager::BusManager(const string &nodePath, const string &edgePath, const string &tagsPath) {

    this->graph = Graph<int>();
    this->prisoners = {};
    this->tags = {
            {"prison", {}},
            {"airport",{}},
            {"court",{}},
            {"train",{}},
            {"police", {}},
            {"hospital", {}}
    };

    this->buses = {};

    this->prisonLocation = -1;

    readGraphNodesFromFile(nodePath);
    readGraphEdgesFromFile(edgePath);
    readGraphTagsFromFile(tagsPath);

    this->readData();
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

            this->graph.addVertex(id,(int)x,(int)y);

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

bool BusManager::hasPath(Prisoner prisoner) //Checks if its possible to pick up the prisoner, deliver him/her, and then return to the prison
{
    graph.dijkstraShortestPath(prisonLocation);
    if(graph.getPath(prisonLocation, prisoner.getStart()).empty()) //Checks if there is at least one path to pick up the prisoner
        return false;
    if(graph.getPath(prisonLocation, prisoner.getDestination()).empty())//Checks if there is at least one path to deliver the prisoner
        return false;
    graph.dijkstraShortestPath(prisoner.getStart());
    if(graph.getPath(prisoner.getStart(), prisonLocation).empty())
        return false;
    graph.dijkstraShortestPath(prisoner.getDestination());
    return !graph.getPath(prisoner.getDestination(), prisonLocation).empty();

}

vector<vector<int>> BusManager::calcMultipleBusPath(){
    vector<vector<int>> results;
    bool emptyHeaps = false;


    //Verificar se para cada prisioneiro ha um autocarro do seu tipo e se houver se este cabe nele
    for(Prisoner & prisoner : prisoners)
    {
        prisoner.reset();
        bool hasBus = false;
        for(auto & bus : buses) {
            if(bus->checkType(prisoner, this->tags) && bus->canFit(prisoner)) {
                hasBus = true;
                break;
            }
        }
        if(!hasBus) {
            prisoner.setAny();
        }
    }

    // Os primeiros caminhos possiveis para cada autocarro
    for(auto & bus : buses){
        vector<Vertex<int>*> dest;
        results.emplace_back();

        for(int i = 0; i< prisoners.size();i++) {
            if(hasPath(prisoners.at(i))) {
                if (bus->checkType(prisoners.at(i), this->tags))
                    dest.push_back(graph.findVertex(prisoners.at(i).getStart()));
            } else {
                prisoners.erase(prisoners.begin()+i);
                i--;
            }

        }
        bus->setDestinations(dest);
    }


    //Enquanto houver destinos possiveis em algum autocarro
    while(!emptyHeaps)
    {
        vector<Vertex<int>*> ignoredVertexes;

        for(int i = 0; i < buses.size() ; i++ ) {

            if (!buses.at(i)->getDestinations().empty()) {
                bool hadAction = false;

                //Calculo do caminho para o proximo destino
                graph.dijkstraShortestPath(buses.at(i)->getLastLocation());
                buses.at(i)->startHeap();

                Vertex<int> *nextDest = buses.at(i)->popHeap();

                vector<int> pathToNext = graph.getPath(buses.at(i)->getLastLocation(), nextDest->getInfo());

                int currentLocation = buses.at(i)->getLastLocation();
                buses.at(i)->setLastLocation(nextDest->getInfo());

                for (auto &prisoner : prisoners) {
                    if(prisoner.getWeight() > buses.at(i)->getMaxCapacity())
                        continue;
                    if (prisoner.getStart() == buses.at(i)->getLastLocation() && !prisoner.isPickedUp()
                    && buses.at(i)->checkType(prisoner,this->tags)) {
                        double currentBusToNextDestDist = nextDest->getDist();
                        for (size_t j = 0; j < buses.size(); j++) {
                            graph.dijkstraShortestPath(buses.at(j)->getLastLocation());
                            double nextDist = nextDest->getDist();
                            bool ignoreDest = false;
                            //Se um outro autocarro estiver para entregar um prisioneiro perto de nextDest, este
                            //ignora este destino para dar prioridade ao outro autocarro
                            for(auto &prisoner1 : prisoners) {
                                if(i != j && prisoner1.isPickedUp() && !prisoner1.isDelivered()
                                && prisoner1.getBusNum() == j && buses.at(j)->checkType(prisoner1,this->tags)) {
                                    graph.dijkstraShortestPath(prisoner1.getDestination());
                                    if (nextDest->getDist() < nextDist) {
                                        ignoredVertexes.push_back(nextDest);
                                        ignoreDest = true;
                                        break;
                                    }
                                }
                            }
                            if (ignoreDest)
                                break;
                            if (i != j && currentBusToNextDestDist > nextDist && buses.at(j)->checkType(prisoner,this->tags)) {
                                ignoredVertexes.push_back(nextDest);
                                break;
                            } else if (j == buses.size() - 1) {
                                if (buses.at(i)->canFit(prisoner)) {
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
                        buses.at(i)->addCurrentCapacity(prisoner.getWeight() * -1);
                        hadAction = true;
                    }
                }

                if (hadAction || buses.at(i)->getDestinations().empty()) {
                    if (!hadAction) {
                        buses.at(i)->setLastLocation(currentLocation);
                    }
                    for (auto &ignoredVertex : ignoredVertexes)
                        buses.at(i)->addDest(ignoredVertex);
                    ignoredVertexes.clear();
                } else {
                    buses.at(i)->setLastLocation(currentLocation);
                    i--;
                }

                //Se o autocarro efetivamente recolheu ou entregou algum prisioneiro, os resultados são inseridos
                if (hadAction) {
                    if (results[i].empty())
                        results[i].insert(results[i].end(), pathToNext.begin(), pathToNext.end());
                    else
                        results[i].insert(results[i].end(), next(pathToNext.begin(), 1), pathToNext.end());
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

    //Calculo do caminho de volta à prisao
    for(int i = 0; i < buses.size(); ++i) {
        graph.dijkstraShortestPath(buses.at(i)->getLastLocation());
        vector<int> pathToPrison = graph.getPath(buses.at(i)->getLastLocation(), prisonLocation);
        results[i].insert(results[i].end(), next(pathToPrison.begin(),1), pathToPrison.end());
    }

    //Eliminar os autocarros que não foram usados e adiciona os sítios com tag visitados pelo autocarros
    for(int i = results.size() - 1; i >= 0; i--) {
        if(results.at(i).size() <= 1) {
            buses.erase(buses.begin() + i);
        } else {
            for(int res : results.at(i)) {
                for (const pair<int, string>& tv : this->getTags()) {
                    if (tv.first == res) {
                        buses.at(i)->addVisited(tv);
                        break;
                    }
                }
            }
        }
    }

    return results;
}

//Função usada numa iteração anterior
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

void BusManager::addBus(Bus *bus) {
    this->buses.push_back(bus);
}

void BusManager::resetPrisoners() {
    this->prisoners = {};
}

void BusManager::resetBuses() {
    this->buses = {};
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

void BusManager::clear() {
    this->prisoners.clear();
    this->buses.clear();
}

void BusManager::readData() { //Lê os ficheiros de prisioneiros e autocarros
    this->clear();

    string line;
    int start, dest, danger;
    char c;
    ifstream in("../src/resources/prisoners.txt");
    getline(in, line);
    while(getline(in, line)) {
        istringstream ss(line);
        ss >> start >> c >> dest >> c >> danger;
        prisoners.emplace_back(start, dest, danger);
    }

    int capacity;
    string typeStr;
    busType type;
    in = ifstream("../src/resources/buses.txt");
    getline(in, line);
    while(getline(in, line)) {
        istringstream ss(line);
        ss >> capacity >> c >> typeStr;
        if(typeStr == "regular")
            type = REGULAR;
        else if(typeStr == "airports")
            type = AIRPORTS;
        else if(typeStr == "any")
            type = ANY;
        else if(typeStr == "trains")
            type = TRAINS;
        else {
            cout << "Invalid bus type!" << endl;
            continue;
        }
        buses.push_back(new Bus(type, this->prisonLocation, capacity));
    }
}

void BusManager::reset() {
    for(auto p : prisoners) {
        p.reset();
    }
    for(auto b : buses) {
        b->reset(prisonLocation);
    }
}


