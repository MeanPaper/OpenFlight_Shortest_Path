#pragma once
#include "Graph.h"
#include "parseGraph.h"
#include <iostream>
#include <unordered_set>
using namespace std;

class Test {
    public:
        /**
        * Compares whether two given files are the same
        * Reference: https://stackoverflow.com/a/37575457
        * @return return true if two files are the same
        * @param p1 file location for the 1st file
        * @param p2 file location for the 2nd file
        */    
        bool compareFiles(const std::string& p1, const std::string& p2);
        /**
        * Validate whether the parsed graph's contains lat/lon data, airport abbreviation that adhere to format.
        * @param g The parsed graph
        */
        void testParse(Graph g);
        /**
        * BFS test case 1 running on a small graph
        */        
        void testBFSSmall1();
        /**
        * BFS test case 2 running on a small graph
        */        
        void testBFSSmall2();
        /**
        * BFS test case 3 running on a small graph
        */        
        void testBFSSmall3();  
        /**
        * BFS test case running on a medium-sized graph
        */                      
        void testBFSMed();
        /**
        * BFS test case running on a large graph (the original complete dataset)
        */        
        void testBFSLarge();
        /**
        * Floyd Warshall test case running on a small-sized graph
        */        
        void testFloydWarshallSmall();
        /**
        * Floyd Warshall test case running on a medium-sized graph
        */        
        void testFloydWarshallMed();
        /**
        * Floyd Warshall test case running on a large graph (the original complete dataset)
        * Note: it takes ~1.5 hours to run it our original dataset is huge and Floyd Warshall is O(V^3) run-time complexity
        * Note: we comment it out since it takes too long to run
        */        
        void testFloydWarshallLarge();
        /**
        * Validate whether the parsed graph has 7697 nodes (airports).
        * @param g The parsed graph
        */
        void validateNodeNo(Graph g);
        /**
        * Validate whether the parsed graph has 67663 edges (distinct flight iternrary).
        * @param g The parsed graph
        */        
        void validateEdgeNo(Graph g);
        /**
        * checks whether a the graph's nodes are valid
        * @param g a parsed graph
        */        
        void validateNodeWithFile(Graph g);
        /**
        * Checks whether the airport abbreviation exists in the original dataset
        * @return return true if an airport exists / returns false if the airport does not exist
        * @param abbr airport abbreviation
        */        
        bool checkAiportExists(std::string abbr);
        /**
        * checks whether a the graph's edges are valid with respect to the source dataset
        * @param g a parsed graph
        */        
        void validateEdgeWithFile(Graph g);
        /**
        * checks whether the graph's edge exists in the original dataset
        * @return return true if the edge exists / return false if the edge does not exist
        * @param start the start airport
        * @param end the destination airport
        */        
        bool checkEdgeExists(std::string start, std::string end);
        /**
        * A* test case running on a small graph
        */
        void AstarTestSmall();
        /**
        * A* test case running on a medium-sized graph
        */        
        void AstarTestMedium();
        /**
        * A* test case running on a large graph (the original complete dataset)
        */        
        void AstarTest();
    private:
};