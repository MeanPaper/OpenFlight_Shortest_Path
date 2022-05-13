#pragma once
#include "Graph.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "parseGraph.h"


using namespace std;

class parseGraph {
    public:
        /**
        * A function to parse the input airport / route stream to an Adjacency List Graph
        * @param g A given graph
        * @param str_ input airport stream
        * @param delimiter input airport route stream
        */    
        void parseCSV(Graph &g, std::ifstream &airport_ifs, std::ifstream &route_ifs);
    private:
        /**
        * Helper function to delimit a given string with a delimiter
        * @return A vector of substrings being delimited
        * @param str_ A given string
        * @param delimiter A given delimiter
        */    
        vector<string> delimit(string str_, string delimiter);
};