#ifndef CAL_PROJ_RENDERER_H
#define CAL_PROJ_RENDERER_H

#include "BusManager.h"
#include "graphviewer.h"


#define MAP_WIDTH           5000
#define MAP_HEIGHT          5000
#define WINDOW_WIDTH        600
#define WINDOW_HEIGHT       600
#define DFLT_VERTEX_COLOR   "blue"
#define DFLT_EDGE_COLOR     "black"

class Renderer {
    BusManager* manager;
    GraphViewer* gv;

public:
    Renderer(BusManager* manager);
    void initWindow();
    void loadVertexes();
    void loadEdges();
    void update();
private:

};


#endif //CAL_PROJ_RENDERER_H
