#include "Renderer.h"
#include <vector>

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
        gv->setVertexLabel(v->getInfo(),to_string(v->getInfo()));
    }
}

void Renderer::loadEdges(){
    int count = 0;
    for(auto v : this->manager->getVertexSet()){
        for (auto e : v->getAdj()) {
            gv->addEdge(count,v->getInfo(),e.getDest()->getInfo(),EdgeType::DIRECTED);
            edges.emplace_back(v->getInfo(),e.getDest()->getInfo());
            ++count;
        }
    }
}

void Renderer::update() {
    this->gv->rearrange();
}

void Renderer::showBusPath() {
    vector<int> path = manager->calcBusPath();
    for(size_t i = 0 ; i < path.size(); ++i) {
        size_t j = path.at(i);
        if(j == manager->getPrisonLocation()){
            gv->setVertexColor(j, PRISON_COLOR);
        } else if(find_if(manager->getPrisoners().begin(),manager->getPrisoners().end(), [j] (const Prisoner& p) { return p.getStart() == j; }) != manager->getPrisoners().end()){
            gv->setVertexColor(j, PATH_START);
        } else if(find_if(manager->getPrisoners().begin(),manager->getPrisoners().end(), [j] (const Prisoner& p) { return p.getDestination() == j; }) != manager->getPrisoners().end()){
            gv->setVertexColor(j, PATH_END);
        } else {
            gv->setVertexColor(j, BUS_COLOR_1);
        }


        if(i < path.size() - 1) {
            int idx = distance(edges.begin(),
                               find(edges.begin(), edges.end(), pair<int, int>{j, path.at(i + 1)})); //Gets the edge id
            gv->setEdgeColor(idx, "green");
        }
    }
}

void Renderer::showBusesPaths(int nBus) {
    vector<vector<int>> busesPath = manager->calcMultipleBusPath(nBus);
    for(auto bp : busesPath) {
        for(auto i : bp) {
            if (i == manager->getPrisonLocation()) {
                gv->setVertexColor(i, PRISON_COLOR);
            } else if (find_if(manager->getPrisoners().begin(), manager->getPrisoners().end(),
                               [i](const Prisoner &p) { return p.getStart() == i; }) != manager->getPrisoners().end()) {
                gv->setVertexColor(i, PATH_START);
            } else if (find_if(manager->getPrisoners().begin(), manager->getPrisoners().end(),
                               [i](const Prisoner &p) { return p.getDestination() == i; }) !=
                       manager->getPrisoners().end()) {
                gv->setVertexColor(i, PATH_END);
            } else {
                gv->setVertexColor(i, BUS_COLOR_1);
            }
        }
    }
}
