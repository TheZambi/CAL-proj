#include "Prisoner.h"

Prisoner::Prisoner(const int &start, const int &dest) {
    this->start = start;
    this->destination = dest;
    this->pickedUp = false;
    this->delivered = false;
    busNumber = -1;
}

int Prisoner::getStart() const {
    return start;
}

int Prisoner::getDestination() const {
    return destination;
}

bool Prisoner::isPickedUp() const {
    return pickedUp;
}

bool Prisoner::isDelivered() const {
    return delivered;
}

int Prisoner::getBusNum() const {
    return busNumber;
}

void Prisoner::pickUp(int busNum) {
    pickedUp = true;
    this->busNumber = busNum;
}

void Prisoner::deliver() {
    delivered = true;
}
