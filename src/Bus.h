#ifndef CAL_PROJ_BUS_H
#define CAL_PROJ_BUS_H
#include "Graph.h"
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
    int num;
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
    int getNum() const;
    void addDest(Vertex<int>* dest);
    void addVisited(pair<int,string> visit);
    int getMaxCapacity() const;
    int getCurrentCapacity() const;
    void addCurrentCapacity(int capacity);
    void setDestinations(vector<Vertex<int>*> &dests);
};


#endif //CAL_PROJ_BUS_H
