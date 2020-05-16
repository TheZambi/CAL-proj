#ifndef CAL_PROJ_MENU_H
#define CAL_PROJ_MENU_H

#include "BusManager.h"
#include "Renderer.h"

class Menu {
    BusManager *manager;
    Renderer *renderer;
    enum State {
        MAIN,
        PRISONER,
        MAP
    } state;
    bool finished;

public:
    Menu(BusManager *busManager, Renderer *renderer);

    void start();

private:
    void readInput();
    void display();
    void finish();
};


#endif //CAL_PROJ_MENU_H
