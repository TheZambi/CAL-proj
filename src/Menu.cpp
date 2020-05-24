#include <sstream>
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
                    this->state = BUS;
                    break;
                case 3:
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
        case BUS:
            int choiceBus;
            cin >> choiceBus;
            switch (choiceBus) {
                case 0:
                    this->state = MAIN;
                    break;
                case 1:
                    addMenu();
                    break;
                case 2:
                    manager->resetBuses();
                    cout << "Buses reset" << endl;
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
                    displayBusPath(choiceMap);
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
            cout << "2) Manage buses" << endl;
            cout << "3) Show path" << endl;
            cout << "0) Quit" << endl;
            break;
        case PRISONER:
            cout << "1) Add prisioner" << endl;
            cout << "2) Reset prisioners" << endl;
            cout << "0) Back" << endl;
            break;
        case BUS:
            cout << "1) Add Bus" << endl;
            cout << "2) Reset Buses" << endl;
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
    if(state == PRISONER) {
        int start;
        int dest;
        int weight;
        cout << "Insert prisioner's" << endl;
        cout << "Start location:" << endl;
        for (const auto &i : manager->getTags()) {
            cout << i.first << " - " << i.second << endl;
        }
        cin >> start;
        cout << "End Location:" << endl;
        for (const auto &i : manager->getTags()) {
            if (i.first != start)
                cout << i.first << " - " << i.second << endl;
        }
        cin >> dest;
        cout << "Danger degree (number of places that they occupy):";
        cin >> weight;
        if (!manager->addPrisoner(Prisoner(start, dest, weight)))
            cout << "Prisioner already exists!" << endl << endl;
        else
            cout << "Prisioner successfuly added" << endl << endl;
    } else if(state == BUS) {
        int capacity;
        string typeStr;
        busType type;
        cout << "Type (regular, airports, trains):" << endl;
        cin >> typeStr;
        cout << "Capacity:" << endl;
        cin >> capacity;
        if(typeStr == "regular") {
            type = REGULAR;
        } else if(typeStr == "trains") {
            type = TRAINS;
        } else if(typeStr == "airports") {
            type = AIRPORTS;
        } else {
            cout << "Invalid bus!" << endl;
        }
        manager->addBus(new Bus(type, manager->getPrisonLocation(), capacity));
        cout << "Bus successfuly added" << endl << endl;
    }
}

void Menu::displayMap() {
    renderer->initWindow();
    renderer->loadVertexes();
    renderer->loadEdges();
    renderer->showBusesPaths();
    renderer->update();
    renderer->printBusesPaths(manager->getBuses());
    cout << endl << "Insert any character to continue" << endl;
}

void Menu::displayBusPath(int busN) {
    renderer->initWindow();
    renderer->loadVertexes();
    renderer->loadEdges();
    renderer->showBusPath(busN);
    renderer->update();
}


