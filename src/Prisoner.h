#ifndef CAL_PROJ_PRISONER_H
#define CAL_PROJ_PRISONER_H


class Prisoner {
    int start;
    int destination;
public:
    Prisoner(const int &start, const int &dest);

    int getStart() const;
    int getDestination() const;
};


#endif //CAL_PROJ_PRISONER_H
