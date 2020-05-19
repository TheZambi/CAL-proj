#include "Prisoner.h"

Prisoner::Prisoner(int start, int dest, int danger) {
    this->start = start;
    this->destination = dest;
    this->pickedUp = false;
    this->delivered = false;
    this->weight = danger;
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

int Prisoner::getWeight() const {
    return this->weight;
}
