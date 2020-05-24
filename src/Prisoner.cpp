#include <iostream>
#include "Prisoner.h"

using namespace std;

Prisoner::Prisoner(int start, int dest, int danger) {
    this->start = start;
    this->destination = dest;
    this->pickedUp = false;
    this->delivered = false;
    this->weight = danger;
    this->any = false;
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

busType Prisoner::getDestType(const map<string,vector<pair<int, string>>> &tags) const  {
    if(any)
        return ANY;
    string type;
    for(auto & tag : tags)
    {
        for(const auto& dest : tag.second)
        {
            if(dest.first==this->destination) {
                type = tag.first;
                break;
            }
        }
        if(!type.empty())
            break;
    }
    if(type=="airport")
        return AIRPORTS;
    else if(type == "train")
        return TRAINS;
    return REGULAR;
}

void Prisoner::setAny() {
    this->any=true;
}

void Prisoner::reset() {
    this->any = false;
    this->delivered = false;
    this->pickedUp = false;
    this->busNumber = -1;
}


