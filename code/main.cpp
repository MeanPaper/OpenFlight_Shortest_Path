#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "Graph.h"
#include "vector"
#include "Test.h"
#include "parseGraph.h"
#include "user.h"

using namespace std;

/**
* The main function to execute the whole program.
* @return returns 0 once the program runs successfully.
*/
int main() {
    Graph g;
    //Test test;
    parseGraph parser;

    std::string airport = "../data/airports.dat";
    std::string routes = "../data/routes.dat";
    std::ifstream airport_ifs(airport);
    std::ifstream route_ifs(routes);
    // parse the graph
    parser.parseCSV(g, airport_ifs, route_ifs); 
    userInteraction(&g);

    return 0;
}