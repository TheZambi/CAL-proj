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

int Bus::getMaxCapacity() const
{
    return maxCapacity;
}

int Bus::getCurrentCapacity() const {
    return currentCapacity;
}

void Bus::addCurrentCapacity(int capacity)
{
    this->currentCapacity += capacity;
}

void Bus::setDestinations(vector<Vertex<int>*> &dests) {
    this->destinations = dests;
    startHeap();
}

