#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <limits>
#include <sstream>
#include <fstream>

class Graph {
    public:
        struct Node {
            int vecIndex;
            //Node* prev;
            double lat;
            double lon;
            double fscore;
            //double gscore;
            //double hscore;
            std::string name; // airport fullname
            std::string abbr; // airport abbreviation
            Node() {
                //gscore = std::numeric_limits<double>::max();

            }
            Node(int vecIndex, double lat, double lon, std::string name, std::string abbr) 
                : vecIndex(vecIndex), lat(lat), lon(lon), name(name), abbr(abbr) 
            {
                // not init vecIndex
                //gscore = std::numeric_limits<double>::max();

            }
            void modifyIndex(int newIndex) {
                this->vecIndex = newIndex;
            }
        };

        struct Edge {
            Node *source;
            Node *dest;

            Edge() {}
            Edge(Node* n1, Node* n2) 
                : source(n1), dest(n2)
            {
            }
        };

    public:
        /**
        * Constructs a Graph with no edge or nodes.
        */    
        Graph();
        /**
        * Destruct the stored Graph.
        */        
        ~Graph();
        std::vector<Node*> all_node;  
        /**
        * Obtain the abbrNodeMap parameter
        * @return the unordered map (key:abbr of airport; value: node)
        */        
        std::unordered_map<std::string, Graph::Node*> getAbbrMap();
        /**
        * get the stored adjList 2d vector parameter
        * @return the stored adjList 2d vector parameter
        */
        std::vector<std::vector<Graph::Edge *>> getAdjList();
        /**
        * Add a node to the Adjacency List Graph
        * @param n A pointer to a given node
        */
        void addNode(Node* n);
        /**
        * Add an edge to the Adjacency List Graph
        * @param n A pointer to a given edge
        */        
        void addEdge(Edge* e);
        /**
        * Return the total number of nodes in the graph.
        * @return the total number of nodes in the graph
        */        
        int nodeNumber();
        /**
        * Compute the distance between the source and destination airport using the great-circle distance formula
        * Reference: https://www.movable-type.co.uk/scripts/latlong.html
        * @return the distance between the source and destination airport
        * @param src node pointer to the source airport
        * @param dest node pointer to the destination airport
        */        
        double computeDist(Node* src, Node* dest);
        /**
        * Convert an airport abbreviation to a node
        * @return the desired node pointer
        * @param abbr an airport abbreviation
        */        
        Node* abbr_to_Node(std::string abbr);
        /**
        * Convert a vector id (airport id) to a node
        * @return the desired node pointer
        * @param n a vector id
        */        
        Node* id_to_Node(int id);
        /**
        * Check whether an airport exists in the graph
        * @return true/false depending on whether the abbreviation exists in the graph
        * @param n airport abbreviation (IATA code)
        */        
        bool exists(std::string abbr);
        /**
        * print the entire map
        */        
        void printMap();
        /**
        * Compute shortest path between the source and destination airport using BFS algorithm
        * @param src the source airport abbreviation
        * @param dest the destination airport abbreviation
        * @param writeToFile if true then write to the a file / if false then output the result to the terminal
        * @param fileName the output file location
        */        
        void BFS(std::string src, std::string dest, bool writeToFile, std::string fileName);
        int edgeCount ; // add for testcase. 
        int delete_flights; // add for testcase.
        /**
        * increments the delte_flight parameter for every call
        */
        void increment_delete_flights(); //add for testcase
        /**
        * Get the stored path string
        * @return the stored path string parameter
        */
        std::string getPath(); //return a string of a path
        /**
        * Print the detailed A* running result to the terminal
        */
        void printDetail(); //print the shortest path
        /**
        * Print the detailed A* running result to a file
        * @param string the output file name
        */        
        void printDetailToFile(std::string fileName); //print the shortest path to file with a name fileName

        //AStar Search priority queue comparator
        typedef struct Compare{
            bool operator()(const Node*node1, const Node*node2){
                return node1->fscore < node2->fscore;
            }
        }Comparator;
        
        /**
        * Compute the shortest path between start and destination airports via A* algorithms
        * @param string the start airport abbr
        * @param string the destination airport abbr
        */ 
        void AStar(std::string start, std::string dest);
        /**
        * Compute the shortest paths between all pairs of start and destination airports via Floyd Warshall algorithm
        * adapted from https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/
        * @param writeToFile if true then write to the a file / if false then output the result to the terminal
        * @param fileName the output file location
        */
        void floydWarshall(bool writeToFile, std::string fileName);
        /**
        * helper function to print floydWarshall() solution as a 2D matrix on the terminal
        * @param dist a 2d vector storing the distances between all pairs of airports
        */
        void printfloydWaSolution(std::vector<std::vector<double>> dist);

    private:
        int adjSize;
        std::unordered_map<int, Node*> idNodeMap; // HM that converts id to node ptr
        std::unordered_map<std::string, Node*> abbrNodeMap; // HM that converts id to node ptr
        std::vector<std::vector<Edge *>> adjList;  // [ORD:[e1:[ EWR], e2: [HKG], e3[JFK]
        std::string pathString;
        std::vector<Node*> nodeList;        
};