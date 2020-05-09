#include "Prisoner.h"

Prisoner::Prisoner(const int &start, const int &dest) {
    this->start = start;
    this->destination = dest;
}

int Prisoner::getStart() const {
    return start;
}

int Prisoner::getDestination() const {
    return destination;
}
