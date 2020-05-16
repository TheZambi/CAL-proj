#include <iostream>
#include <string>
#include "BusManager.h"
#include "Renderer.h"
#include "Menu.h"

//#define NODES_FILE "../src/resources/maps/GridGraphs/16x16/nodes.txt"
//#define EDGES_FILE "../src/resources/maps/GridGraphs/16x16/edges.txt"
//#define NODES_FILE "../src/resources/maps/Ermesinde/nodes_x_y_ermesinde.txt"
//#define EDGES_FILE "../src/resources/maps/Ermesinde/edges_ermesinde.txt"
#define NODES_FILE  "../src/resources/maps/TesteEspinho/nodes.txt"
#define EDGES_FILE  "../src/resources/maps/TesteEspinho/edges.txt"
#define TAGS_FILE   "../src/resources/maps/TesteEspinho/tags.txt"


int main() {
//    vector<Prisoner> prisoners = {Prisoner(5, 25),
//                                  Prisoner(48,105)};

//    vector<Prisoner> prisoners = {Prisoner(1183721318, 1193124746),
//                                  Prisoner(1183721287,1173440023)};


    vector<Prisoner> prisoners = {Prisoner(148,430),Prisoner(1, 377), Prisoner(861, 66),
                                  Prisoner(689, 1)};

    //BusManager manager = BusManager(NODES_FILE, EDGES_FILE, 0, prisoners);
    BusManager manager = BusManager(NODES_FILE, EDGES_FILE, TAGS_FILE, prisoners);
    Renderer renderer = Renderer(&manager);
    Menu menu(&manager, &renderer);

    menu.start();

//    renderer.initWindow();
//    renderer.loadVertexes();
//    renderer.loadEdges();
//    //renderer.showBusPath();
//    renderer.showBusesPaths(3);
//    renderer.update();

    getchar();
    return 0;
}
