#ifndef CAL_PROJ_BUS_H
#define CAL_PROJ_BUS_H
#include "Graph.h"
#include "Prisoner.h"

enum busType {
    REGULAR,
    AIRPORTS,
    TRAINS
};

class Compare
{
public:
    bool operator() (Vertex<int> *a, Vertex<int> *b)
    {
        return a->getDist() > b->getDist();
    }
};

class Bus {
    vector<Vertex<int>*> destinations;
    vector<pair<int, string>> visited;
    int last_location;
    busType type;
    int maxCapacity;
    int currentCapacity; //used to track how much capacity is being used
public:
    vector<pair<int,string>> getVisited();
    Bus(busType type, int last_location, int capacity);

    busType getType() const;
    vector<Vertex<int>*> getDestinations() const;
    void startHeap();
    Vertex<int>* popHeap();
    int getLastLocation() const;
    void setLastLocation(int location);
    void addDest(Vertex<int>* dest);
    void addVisited(const pair<int,string> &visit);
    void addCurrentCapacity(int capacity);
    void setDestinations(vector<Vertex<int>*> &dests);
    bool canFit(const Prisoner &p) const;
};


#endif //CAL_PROJ_BUS_H
