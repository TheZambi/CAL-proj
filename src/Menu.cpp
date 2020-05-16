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
            this->state = MAIN;
            break;
        case MAP:
            char wait;
            cin >> wait;
            renderer->closeWindow();
            this->state = MAIN;
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
            cout << "1) Add prisoners" << endl;
            cout << "2) Show path" << endl;
            cout << "0) Quit" << endl;
            break;
        case PRISONER:
            cout << "Insert Prisoner Start Location: " << endl;
            for(int i = 0; i < 0; ++i) {
                //Locations here
            }
            break;
        case MAP:
            renderer->initWindow();
            renderer->loadVertexes();
            renderer->loadEdges();
            renderer->showBusesPaths(3);
            renderer->update();
            break;
    }
}

void Menu::finish() {
    this->finished = true;
}


