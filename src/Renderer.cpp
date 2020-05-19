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
    //this->gv->defineEdgeCurved(false);
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
            gv->setVertexColor(j, path_color[0]);
        }


        if(i < path.size() - 1) {
            int idx = distance(edges.begin(),
                               find(edges.begin(), edges.end(), pair<int, int>{j, path.at(i + 1)})); //Gets the edge id
            gv->setEdgeColor(idx, path_color[0]);
        }
    }
}

void Renderer::closeWindow() {
    gv->closeWindow();
}

void Renderer::showBusesPaths(int nBus) {
    vector<vector<int>> busesPath = manager->calcMultipleBusPath(nBus);

    for(size_t j = 0; j < busesPath.size();++j){
        for(size_t a = 0; a < busesPath.at(j).size(); ++a) {
            int i = busesPath.at(j).at(a);
            if (find_if(manager->getPrisoners().begin(), manager->getPrisoners().end(),
                               [i](const Prisoner &p) { return p.getStart() == i; }) != manager->getPrisoners().end()) {
                gv->setVertexColor(i, PATH_START);
            } else if (find_if(manager->getPrisoners().begin(), manager->getPrisoners().end(),
                               [i](const Prisoner &p) { return p.getDestination() == i; }) !=
                       manager->getPrisoners().end()) {
                gv->setVertexColor(i, PATH_END);
            } else {
                gv->setVertexColor(i, path_color[j]);
            }

            if(a < busesPath.at(j).size() - 1) {
                int idx = distance(edges.begin(),
                                   find(edges.begin(), edges.end(), pair<int, int>{i, busesPath.at(j).at(a + 1)})); //Gets the edge id
                gv->setEdgeColor(idx, path_color[j]);
                gv->setEdgeThickness(idx, 5);
            }
        }
    }
    gv->setVertexColor(manager->getPrisonLocation(), PRISON_COLOR);
}

void Renderer::showBusPath(int busN, int nBus) {
    vector<vector<int>> busesPath = manager->calcMultipleBusPath(nBus);

    for(size_t a = 0; a < busesPath.at(busN).size(); ++a) {
        int i = busesPath.at(busN).at(a);
        if (find_if(manager->getPrisoners().begin(), manager->getPrisoners().end(),
                    [i, busN](const Prisoner &p) { return p.getStart() == i && p.getBusNum() == busN; }) != manager->getPrisoners().end()) {
            gv->setVertexColor(i, PATH_START);
        } else if (find_if(manager->getPrisoners().begin(), manager->getPrisoners().end(),
                           [i, busN](const Prisoner &p) { return p.getDestination() == i && p.getBusNum() == busN; }) !=
                   manager->getPrisoners().end()) {
            gv->setVertexColor(i, PATH_END);
        } else {
            gv->setVertexColor(i, path_color[busN]);
        }

        if(a < busesPath.at(busN).size() - 1) {
            int idx = distance(edges.begin(),
                               find(edges.begin(), edges.end(), pair<int, int>{i, busesPath.at(busN).at(a + 1)})); //Gets the edge id
            gv->setEdgeColor(idx, path_color[busN]);
            gv->setEdgeThickness(idx, 5);
        }
    }
    gv->setVertexColor(manager->getPrisonLocation(), PRISON_COLOR);
}

void Renderer::printBusesPaths(vector<Bus *> buses) {
    for(size_t i = 0; i < buses.size(); ++i) {
        cout << "Bus " << i << endl;
        for(size_t j = 0; j < buses.at(i)->getVisited().size(); ++j) {
            if(j < buses.at(i)->getVisited().size() - 1)
                cout << buses.at(i)->getVisited().at(j).first << ": " << buses.at(i)->getVisited().at(j).second << " -> ";
            else
                cout << buses.at(i)->getVisited().at(j).first << ": " << buses.at(i)->getVisited().at(j).second << endl;
        }
        cout << endl;
    }
}
