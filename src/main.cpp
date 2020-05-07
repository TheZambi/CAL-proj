#include <iostream>
#include <string>
#include "BusManager.h"
#include "Renderer.h"


int main() {
    BusManager manager = BusManager("../src/resources/maps/GridGraphs/16x16/nodes.txt","../src/resources/maps/GridGraphs/16x16/edges.txt");
//    BusManager manager = BusManager("../src/resources/maps/Ermesinde/nodes_x_y_ermesinde.txt","../src/resources/maps/Ermesinde/edges_ermesinde.txt");


    Renderer renderer = Renderer(&manager);

    renderer.initWindow();
    renderer.loadVertexes();
    renderer.loadEdges();
    renderer.update();


    /*
    graph.dijkstraShortestPath(0);
    vector<int> shortestPath = graph.getPath(0,60);
    for(int i : shortestPath) {
        cout << i << endl;
        gv->setVertexColor(i, "green");

    }

    gv->rearrange();

    */

    getchar();
    return 0;
}
