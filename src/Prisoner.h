#ifndef CAL_PROJ_PRISONER_H
#define CAL_PROJ_PRISONER_H

#include <map>
#include <string>
#include <vector>

using namespace std;


typedef enum {
    REGULAR,
    AIRPORTS,
    TRAINS,
    ANY
} busType;

class Prisoner {
    int start;
    int destination;
    bool pickedUp;
    bool delivered;
    int busNumber;
    int weight;
    bool any;

public:
    Prisoner(int start, int dest, int danger);

    void pickUp(int busNum);
    void deliver();

    bool isPickedUp() const;
    bool isDelivered() const;

    int getStart() const;
    int getDestination() const;
    int getWeight() const;
    int getBusNum() const;
    busType getDestType(const map<string,vector<pair<int, string>>> &tags) const;
    void setAny();

};


#endif //CAL_PROJ_PRISONER_H
