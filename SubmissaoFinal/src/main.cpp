#include <string>
#include "BusManager.h"
#include "Renderer.h"
#include "Menu.h"

#define NODES_FILE  "../src/resources/maps/TesteEspinho/nodes.txt"
#define EDGES_FILE  "../src/resources/maps/TesteEspinho/edges.txt"
#define TAGS_FILE   "../src/resources/maps/TesteEspinho/tags.txt"


int main() {

    BusManager manager = BusManager(NODES_FILE, EDGES_FILE, TAGS_FILE);
    Renderer renderer = Renderer(&manager);
    Menu menu(&manager, &renderer);

    menu.start();

    getchar();
    return 0;
}
