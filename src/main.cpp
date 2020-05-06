#include <iostream>
#include <string>
#include "Graph.h"
#include <fstream>
#include <vector>
#include <sstream>
#include "graphviewer.h"


void readGraphNodesFromFile(Graph<int>* graph, string pathToFile){

    ifstream in(pathToFile);

    int count = 0;
    char c;
    double x = 0,y = 0;
    int id;
    string line;

    if(in.is_open()){
        while (getline(in,line)){
            if(count == 0){ //Number of nodes
                ++count;
                continue;
            }
            istringstream ss(line);
            ss >> c >> id >> c >> x >> c >> y;

            graph->addVertex(id,x,y);
        }
    }

    in.close();
}


void readGraphEdgesFromFile(Graph<int>* graph, string pathToFile){

    ifstream in(pathToFile);

    int count = 0;
    char c;
    int id1,id2;
    string line;

    if(in.is_open()){
        while (getline(in,line)){
            if(count == 0){ //Number of nodes
                ++count;
                continue;
            }

            istringstream ss(line);
            ss >> c >> id1 >> c >> id2 >> c;

            graph->addEdge(id1,id2,graph->calculateVertexDistance(id2,id1));
        }
    }

    in.close();
}


int main() {
    Graph<int> graph;

//    readGraphNodesFromFile(&graph,"../src/resources/maps/Ermesinde/nodes_x_y_ermesinde.txt");
    readGraphNodesFromFile(&graph,"../src/resources/maps/GridGraphs/16x16/nodes.txt");

//    readGraphEdgesFromFile(&graph,"../src/resources/maps/Ermesinde/edges_ermesinde.txt");
    readGraphEdgesFromFile(&graph,"../src/resources/maps/GridGraphs/16x16/edges.txt");


    GraphViewer *gv = new GraphViewer(5000, 5000, false);
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    int minY = std::numeric_limits<int>::max();
    int minX = std::numeric_limits<int>::max();
    for(size_t i = 0; i < graph.getVertexSet().size(); ++i){
        Vertex<int>* aux = graph.getVertexSet().at(i);
        if(aux->getY() < minY)
            minY = aux->getY();
        if(aux->getX() < minX)
            minX = aux->getX();
    }



    for(size_t i = 0; i < graph.getVertexSet().size(); ++i){
        Vertex<int>* aux = graph.getVertexSet().at(i);
        gv->addNode(aux->getInfo(), aux->getX() - minX, aux->getY() - minY);
    }

    int count = 0;
    for(size_t i = 0; i < graph.getVertexSet().size(); ++i){
        for (int j = 0; j < graph.getVertexSet().at(i)->getAdj().size(); ++j) {
            Edge<int> aux = graph.getVertexSet().at(i)->getAdj().at(j);
            gv->addEdge(count,graph.getVertexSet().at(i)->getInfo(),aux.getDest()->getInfo(),EdgeType::DIRECTED);
            ++count;
        }
    }



    gv->rearrange();

    graph.dijkstraShortestPath(0);
    vector<int> shortestPath = graph.getPath(0,60);
    for(int i : shortestPath) {
        cout << i << endl;
        gv->setVertexColor(i, "green");

    }

    gv->rearrange();

    getchar();
    return 0;
}
