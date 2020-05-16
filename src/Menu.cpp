#include "Menu.h"

Menu::Menu(BusManager *busManager, Renderer *renderer) {
    this->manager = busManager;
    this->renderer = renderer;
    this->finished = false;
    this->state = MAIN;
}

void Menu::start() {
    while(!finished) {
        display();
        readInput();
    }
}

void Menu::readInput() {
    fflush(stdout);
    switch (state) {
        case MAIN:
            int choice;
            cin >> choice;
            switch (choice) {
                case 0:
                    finish();
                    break;
                case 1:
                    this->state = PRISONER;
                    break;
                case 2:
                    this->state = MAP;
                    break;
                default:
                    break;
            }
            break;
        case PRISONER:
            int choicePris;
            cin >> choicePris;
            switch (choicePris) {
                case 0:
                    this->state = MAIN;
                    break;
                case 1:
                    addMenu();
                    break;
                case 2:
                    manager->resetPrisoners();
                    cout << "Prisioners reset" << endl;
                    break;
                default:
                    break;
            }
            break;
        case MAP:
            int choiceMap;
            cin >> choiceMap;
            switch(choiceMap) {
                case 0:
                    this->state = MAIN;
                    break;
                case 1:
                    cout << "Bus number: ";
                    cin >> choiceMap;
                    displayBusPath(choiceMap, 5);
                    break;
                case 2:
                    displayMap();
                    char wait;
                    fflush(stdout);
                    cin >> wait;
                    renderer->closeWindow();
                    this->state = MAIN;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

}

void Menu::display() {
    switch (state) {
        case MAIN:
            cout << ":::::MEAT WAGONS::::" << endl;
            cout << "--------------------" << endl;
            cout << "1) Manage prisoners" << endl;
            cout << "2) Show path" << endl;
            cout << "0) Quit" << endl;
            break;
        case PRISONER:
            cout << "1) Add prisioner" << endl;
            cout << "2) Reset prisioners" << endl;
            cout << "0) Back" << endl;
            break;
        case MAP:
            cout << "1) One bus" << endl;
            cout << "2) All" << endl;
            cout << "0) Back" << endl;
            break;
    }
}

void Menu::finish() {
    this->finished = true;
}

void Menu::addMenu() {
    int start;
    int dest;
    cout << "Insert prisioner's" << endl;
    cout << "Start location:" << endl;
    for(const auto &i : manager->getTags()) {
        cout << i.first << " - " << i.second << endl;
    }
    cin >> start;
    cout << "End Location:" << endl;
    for(const auto &i : manager->getTags()) {
        if(i.first != start)
            cout << i.first << " - " << i.second << endl;
    }
    cin >> dest;
    if(!manager->addPrisoner(Prisoner(start, dest)))
        cout << "Prisioner already exists!" << endl << endl;
    else
        cout << "Prisioner successfuly added" << endl << endl;
}

void Menu::displayMap() {
    renderer->initWindow();
    renderer->loadVertexes();
    renderer->loadEdges();
    renderer->showBusesPaths(5);
    renderer->update();
}

void Menu::displayBusPath(int busN, int nBus) {
    renderer->initWindow();
    renderer->loadVertexes();
    renderer->loadEdges();
    renderer->showBusPath(busN, nBus);
    renderer->update();
}


