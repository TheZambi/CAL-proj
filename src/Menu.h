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
    void addMenu();
    void display();
    void finish();
    void displayMap();
    void displayBusPath(int busN, int nBus);
};


#endif //CAL_PROJ_MENU_H
