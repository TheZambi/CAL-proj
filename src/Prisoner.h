#ifndef CAL_PROJ_PRISONER_H
#define CAL_PROJ_PRISONER_H


class Prisoner {
    int start;
    int destination;
    bool pickedUp;
    bool delivered;
    int busNumber;
    int weight = 1;

public:
    bool isPickedUp() const;

    bool isDelivered() const;

    Prisoner(const int &start, const int &dest);

    int getStart() const;
    int getDestination() const;

    void pickUp(int busNum);
    int getBusNum() const;
    void deliver();

    int getWeight() const;
};


#endif //CAL_PROJ_PRISONER_H
