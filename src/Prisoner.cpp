#include "Prisoner.h"

Prisoner::Prisoner(const int &start, const int &dest) {
    this->start = start;
    this->destination = dest;
    this->pickedUp = false;
    this->delivered = false;
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

void Prisoner::pickUp() {
    pickedUp = true;
}

void Prisoner::deliver() {
    delivered = true;
}
