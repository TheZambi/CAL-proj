#include "Bus.h"

Bus::Bus(vector<Vertex<int>*> destinations, busType type, int last_location) {
    this->destinations = destinations;
    this->type = type;
    this->last_location = last_location;
    startHeap();
}

vector<Vertex<int>*> Bus::getDestinations() const {
    return destinations;
}

busType Bus::getType() const {
    return type;
}

void Bus::startHeap() {
    make_heap(destinations.begin(), destinations.end(), Compare());
}

int Bus::getLastLocation() const {
    return last_location;
}

Vertex<int>* Bus::popHeap() {
    Vertex<int>* v = destinations.front();
    pop_heap(destinations.begin(), destinations.end());
    destinations.pop_back();
    return v;
}

void Bus::setLastLocation(int location) {
    this->last_location = location;
}

int Bus::getNum() const {
    return num;
}

void Bus::addDest(Vertex<int>* dest) {
    destinations.push_back(dest);
}

void Bus::addVisited(pair<int, string> visit) {
    visited.push_back(visit);
}

vector<pair<int, string>> Bus::getVisited() {
    return visited;
}

