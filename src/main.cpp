#include <iostream>
#include <string>
#include "BusManager.h"
#include "Renderer.h"

#define NODES_FILE "../src/resources/maps/GridGraphs/16x16/nodes.txt"
#define EDGES_FILE "../src/resources/maps/GridGraphs/16x16/edges.txt"
//#define NODES_FILE "../src/resources/maps/Ermesinde/nodes_x_y_ermesinde.txt"
//#define EDGES_FILE "../src/resources/maps/Ermesinde/edges_ermesinde.txt"


int main() {
    BusManager manager = BusManager(NODES_FILE, EDGES_FILE, 0, Prisoner(10, 64));

    Renderer renderer = Renderer(&manager);

    renderer.initWindow();
    renderer.loadVertexes();
    renderer.loadEdges();
    renderer.showBusPath();
    renderer.update();

    getchar();
    return 0;
}
