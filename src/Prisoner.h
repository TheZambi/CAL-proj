#ifndef CAL_PROJ_PRISONER_H
#define CAL_PROJ_PRISONER_H


class Prisoner {
    int start;
    int destination;
    bool pickedUp;
    bool delivered;
    int busNumber;

public:
    bool isPickedUp() const;

    bool isDelivered() const;

    Prisoner(const int &start, const int &dest);

    int getStart() const;
    int getDestination() const;

    void pickUp(int busNum);
    int getBusNum();
    void deliver();
};


#endif //CAL_PROJ_PRISONER_H
