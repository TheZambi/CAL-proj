#ifndef CAL_PROJ_BUS_H
#define CAL_PROJ_BUS_H
#include "Graph.h"
#include "Prisoner.h"


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
    Bus(busType type, int last_location, int capacity);

    void startHeap();
    Vertex<int>* popHeap();

    void addDest(Vertex<int>* dest);
    void addVisited(const pair<int,string> &visit);
    void addCurrentCapacity(int capacity);

    void setDestinations(vector<Vertex<int>*> &dests);
    void setLastLocation(int location);

    bool canFit(const Prisoner &p) const;
    int getLastLocation() const;
    int getMaxCapacity() const;
    busType getType() const;
    vector<pair<int,string>> getVisited();
    vector<Vertex<int>*> getDestinations() const;
    bool checkType(Prisoner prisoner,const map<string,vector<pair<int, string>>> &tags) const;
};


#endif //CAL_PROJ_BUS_H
