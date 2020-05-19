#include "Bus.h"

Bus::Bus(busType type, int last_location, int capacity) {
    this->maxCapacity = capacity;
    this->currentCapacity = 0;
    this->type = type;
    this->last_location = last_location;
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

void Bus::addDest(Vertex<int>* dest) {
    destinations.push_back(dest);
}

void Bus::addVisited(const pair<int, string> &visit) {
    visited.push_back(visit);
}

vector<pair<int, string>> Bus::getVisited() {
    return visited;
}

void Bus::addCurrentCapacity(int capacity)
{
    this->currentCapacity += capacity;
}

void Bus::setDestinations(vector<Vertex<int>*> &dests) {
    this->destinations = dests;
    startHeap();
}

bool Bus::canFit(const Prisoner &p) const {
    return currentCapacity + p.getWeight() <= maxCapacity;
}

