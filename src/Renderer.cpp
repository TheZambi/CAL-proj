#include "Renderer.h"

Renderer::Renderer(BusManager* manager) {
    this->manager = manager;
    this->gv = new GraphViewer(MAP_WIDTH, MAP_HEIGHT,false);
}

void Renderer::initWindow(){
    this->gv->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    this->gv->defineVertexColor(DFLT_VERTEX_COLOR);
    this->gv->defineEdgeColor(DFLT_EDGE_COLOR);
}

void Renderer::loadVertexes(){
    for(auto v : this->manager->getVertexSet()){
        gv->addNode(v->getInfo(), v->getX() - manager->getMinX(), v->getY() - manager->getMinY());
    }
}

void Renderer::loadEdges(){
    int count = 0;
    for(auto v : this->manager->getVertexSet()){
        for (auto e : v->getAdj()) {
            gv->addEdge(count,v->getInfo(),e.getDest()->getInfo(),EdgeType::DIRECTED);
            ++count;
        }
    }
}

void Renderer::update() {
    this->gv->rearrange();
}
