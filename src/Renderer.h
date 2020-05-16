#ifndef CAL_PROJ_RENDERER_H
#define CAL_PROJ_RENDERER_H

#include "BusManager.h"
#include "graphviewer.h"
#include <string>


#define MAP_WIDTH           5000
#define MAP_HEIGHT          5000
#define WINDOW_WIDTH        600
#define WINDOW_HEIGHT       600
#define DFLT_VERTEX_COLOR   BLUE
#define DFLT_EDGE_COLOR     BLACK
#define PRISON_COLOR        BLACK
#define PATH_START          YELLOW
#define PATH_END            RED

class Renderer {
    BusManager* manager;
    GraphViewer* gv;

    vector<pair<int,int>> edges;

    const string path_color[6] = {ORANGE,GREEN,PINK,YELLOW,CYAN,GRAY};

public:
    Renderer(BusManager* manager);
    void initWindow();
    void loadVertexes();
    void loadEdges();
    void update();
    void showBusPath();

    void closeWindow();
    void showBusesPaths(int i);

};


#endif //CAL_PROJ_RENDERER_H
