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
    int last_location;
    busType type;
    int num;

public:
    Bus(vector<Vertex<int>*> destinations, busType type, int last_location);

    busType getType() const;
    vector<Vertex<int>*> getDestinations() const;
    void startHeap();
    Vertex<int>* popHeap();
    int getLastLocation() const;
    void setLastLocation(int location);
    int getNum() const;
    void addDest(Vertex<int>* dest);
};


#endif //CAL_PROJ_BUS_H
