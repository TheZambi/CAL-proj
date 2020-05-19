#ifndef CAL_PROJ_PRISONER_H
#define CAL_PROJ_PRISONER_H


class Prisoner {
    int start;
    int destination;
    bool pickedUp;
    bool delivered;
    int busNumber;
    int weight;

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
};


#endif //CAL_PROJ_PRISONER_H
