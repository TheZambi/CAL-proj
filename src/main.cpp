#include <iostream>
#include <string>
#include "BusManager.h"
#include "Renderer.h"

//#define NODES_FILE "../src/resources/maps/GridGraphs/16x16/nodes.txt"
//#define EDGES_FILE "../src/resources/maps/GridGraphs/16x16/edges.txt"
#define NODES_FILE "../src/resources/maps/Ermesinde/nodes_x_y_ermesinde.txt"
#define EDGES_FILE "../src/resources/maps/Ermesinde/edges_ermesinde.txt"


int main() {
//    vector<Prisoner> prisoners = {Prisoner(5, 25),
//                                  Prisoner(48,105)};

    vector<Prisoner> prisoners = {Prisoner(1183721318, 1193124746),
                                  Prisoner(1183721287,1173440023)};
    //BusManager manager = BusManager(NODES_FILE, EDGES_FILE, 0, prisoners);
    BusManager manager = BusManager(NODES_FILE, EDGES_FILE, 1155503714, prisoners);
    Renderer renderer = Renderer(&manager);

    renderer.initWindow();
    renderer.loadVertexes();
    renderer.loadEdges();
    renderer.showBusPath();
    renderer.update();

    getchar();
    return 0;
}
