#include <string>
#include "BusManager.h"
#include "Renderer.h"
#include "Menu.h"

#define NODES_FILE  "../src/resources/maps/TesteEspinho/nodes.txt"
#define EDGES_FILE  "../src/resources/maps/TesteEspinho/edges.txt"
#define TAGS_FILE   "../src/resources/maps/TesteEspinho/tags.txt"


int main() {
//    vector<Prisoner> prisoners = {Prisoner(5, 25),
//                                  Prisoner(48,105)};

//    vector<Prisoner> prisoners = {Prisoner(1183721318, 1193124746),
//                                  Prisoner(1183721287,1173440023)};


//    vector<Prisoner> prisoners = {Prisoner(148,430),Prisoner(1, 377), Prisoner(861, 66),
//                                  Prisoner(689, 1)};

    //vector<Prisoner> prisoners = {};//Prisoner(174,82,3),Prisoner(1, 744,1), Prisoner(739, 92,1),
                                  //Prisoner(1, 260,1), Prisoner(742,885,1), Prisoner(630, 793,1)};

//    vector<Prisoner> prisoners = {Prisoner(1,214),Prisoner(1,260)
//                                 };

    BusManager manager = BusManager(NODES_FILE, EDGES_FILE, TAGS_FILE);
    Renderer renderer = Renderer(&manager);
    Menu menu(&manager, &renderer);

    menu.start();

    getchar();
    return 0;
}
