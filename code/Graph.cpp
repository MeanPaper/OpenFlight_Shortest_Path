#define _USE_MATH_DEFINES

#include <cmath>
#include "Graph.h"
#define Earth_radius 6371e3

using std::priority_queue;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;
using std::string;

/**
 * Constructs a Graph with no edge or nodes.
 */
Graph::Graph() {
    adjSize = 0;
    edgeCount = 0;
    delete_flights = 0;
};

/**
 * Destruct the stored Graph.
 */
Graph::~Graph() {

};

/**
 * Add a node to the Adjacency List Graph
 * @param n A pointer to a given node
 */
void Graph::addNode(Node* n) {
    n->modifyIndex(adjSize);   // update node n's vector 
    std::vector<Edge *> tmp;
    adjList.push_back(tmp); // update our adjList
    idNodeMap[adjSize] = n;   // update HashMap  
    abbrNodeMap[n->abbr] = n; // update HashMap 
    adjSize += 1;              // increment # of nodes
    all_node.push_back(n);
}

/**
 * Add an edge to the Adjacency List Graph
 * @param n A pointer to a given edge
 */
void Graph::addEdge(Edge* e) {
    adjList[e->source->vecIndex].push_back(e);
    edgeCount ++; //add for testcase; 
}

/**
 * Return the total number of nodes in the graph.
 * @return the total number of nodes in the graph
 */
int Graph::nodeNumber() {
    return adjList.size();
}

/**
 * Obtain the abbrNodeMap parameter
 * @return the unordered map (key:abbr of airport; value: node)
 */
std::unordered_map<std::string, Graph::Node*> Graph::getAbbrMap() {
    return abbrNodeMap;
}

/**
 * Convert an airport abbreviation to a node
 * @return the desired node pointer
 * @param abbr an airport abbreviation
 */
Graph::Node* Graph::abbr_to_Node(std::string abbr){
    try {
        return abbrNodeMap.at(abbr);
    } catch (std::out_of_range& e){
        std::cerr << e.what() << std::endl;
        std::cout << "abbr: " << abbr << std::endl;
    }
}

/**
 * Convert a vector id (airport id) to a node
 * @return the desired node pointer
 * @param n a vector id
 */
Graph::Node* Graph::id_to_Node(int id) {
    return idNodeMap.at(id);
}

/**
 * print the entire map
 */
void Graph::printMap(){
    for (auto it = abbrNodeMap.cbegin(); it != abbrNodeMap.cend(); ++it) {
        if ((*it).first == "AER") {
            std::cout << "count: " << abbrNodeMap.count("AER") << std::endl;
        std::cout << "abbr: " << (*it).first << std::endl;
        }
    }
}

/**
 * Check whether an airport exists in the graph
 * @return true/false depending on whether the abbreviation exists in the graph
 * @param n airport abbreviation (IATA code)
 */
bool Graph::exists(std::string abbr) {
    if (abbrNodeMap.count(abbr)) {
        //std::cout << abbr << " exists" << std::endl;
        return true;
    }
    return false;
}

/**
 * Compute the distance between the source and destination airport using the great-circle distance formula
 * Reference: https://www.geeksforgeeks.org/program-distance-two-points-earth/
 * @return the distance between the source and destination airport
 * @param src node pointer to the source airport
 * @param dest node pointer to the destination airport
 */
double Graph::computeDist(Node* src, Node* dest){
    double latSrc = (src->lat)*M_PI/180.0; //src lat in radian
    double latDest = (dest->lat)*M_PI/180.0; //dest lat in radian
    double lonSrc = (src->lon)*M_PI / 180.0;
    double lonDest = (dest->lon)*M_PI / 180.0;

    double lat_diff = latDest-latSrc;
    double lon_diff = lonSrc - lonDest; //longitude difference
    
    double a = pow(sin(lat_diff/2.0),2) + cos(latSrc)*cos(latDest)*pow(sin(lon_diff/2.0),2); 
    double c = 2.0 * asin(sqrt(a));
    double final_distance = Earth_radius * c;
    return final_distance;
}

/**
 * get the stored adjList 2d vector parameter
 * @return the stored adjList 2d vector parameter
 */
std::vector<std::vector<Graph::Edge *>> Graph::getAdjList() {
    return adjList;
}

/**
 * Compute shortest path between the source and destination airport using BFS algorithm
 * @param src the source airport abbreviation
 * @param dest the destination airport abbreviation
 * @param writeToFile if true then write to the a file / if false then output the result to the terminal
 * @param fileName the output file location
 */
void Graph::BFS(std::string src, std::string dest, bool writeToFile, std::string fileName) {
    std::queue<std::string> q;
    std::unordered_set<std::string> visited;
    std::unordered_map<std::string, std::string> predecessor;
    q.push(src);
    visited.insert(src);
    while (!q.empty()) {
        std::string cur = q.front();  // pop the current Abbr from queue
        //std::cout << "node: " << cur << std::endl;
        q.pop();
        if (cur == dest) {
            break;
        }
        Node * curAbbr = abbr_to_Node(cur);
        //std::cout << "idx: " << curAbbr->vecIndex << " abbr: " << curAbbr->abbr << std::endl;
        for (Edge* e: adjList[curAbbr->vecIndex]) {
            if (visited.count(e->dest->abbr) == 0) { // not visited
                visited.insert(e->dest->abbr);
                q.push(e->dest->abbr);
                
                predecessor[e->dest->abbr] = curAbbr->abbr;
                //std::cout << "dest: " << e->dest->abbr << " cur: " << curAbbr->abbr << std::endl;
            }
        }
    }
    std::vector<std::string> res;
    std::string cur = dest;
    res.push_back(cur);
    // cur = predecessor[cur];
    while (predecessor.count(cur)) {
        //std::cout << "cur is: " << cur << std::endl;
        cur = predecessor[cur];
        res.push_back(cur);
    }
    std::reverse(res.begin(), res.end());
    std::fstream outputFS(fileName, std::fstream::out | std::fstream::trunc);
    std::stringstream line;    
    if (writeToFile){
        for (size_t i = 0; i < res.size(); i++) {
            if (i != res.size() - 1) {
                line << res[i] << " " << ">> ";
            }
            else {
                line << res[i];
            }
        }
        outputFS << line.str();
    } else {
    cout << "START BFS SHORTEST PATH SEARCH" << endl;
    cout << "==========================================" << endl;        
        for (size_t i = 0; i < res.size(); i++) {
            if (i != res.size() - 1) {
                std::cout << res[i] << " " << ">>";
            }
            else {
                std::cout << res[i];
            }
        }
        std::cout << std::endl;
    }
    outputFS.close();
}

/**
 * increments the delte_flight parameter for every call
 */
void Graph::increment_delete_flights(){
    delete_flights ++;
}

/**
 * helper function to print floydWarshall() solution as a 2D matrix on the terminal
 * @param dist a 2d vector storing the distances between all pairs of airports
 */
void Graph::printfloydWaSolution(std::vector<std::vector<double>> dist)
{
	cout << "The following matrix shows the shortest "
			"distances"
			" between every pair of vertices \n";
    for (int i = 0; i < adjSize; i++) {
        cout << id_to_Node(i)->abbr << "	 ";
    }
    cout << endl;
	for (int i = 0; i < adjSize; i++) {
		for (int j = 0; j < adjSize; j++) {
            cout << id_to_Node(i)->abbr << "	 ";
			if (dist[i][j] == std::numeric_limits<double>::max())
				cout << "INF"
					<< "	 ";
			else
				cout << dist[i][j] << "	 ";
		}
		cout << endl;
	}
}

/**
 * Compute the shortest paths between all pairs of start and destination airports via Floyd Warshall algorithm
 * adapted from https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/
 * @param writeToFile if true then write to the a file / if false then output the result to the terminal
 * @param fileName the output file location
 */
void Graph::floydWarshall(bool writeToFile, std::string fileName){
    std::vector<std::vector<double>> dist(adjSize, std::vector<double>(adjSize, std::numeric_limits<double>::max()));
    for (int i = 0; i < adjSize; i++) {
        for (int j = 0; j < adjSize; j++) {
            if (i == j){
                dist[i][j] = 0.0;   
            }
        }
    }
    //std::cout << "fill in dist" << std::endl;	
	// initialize the graph
    for (size_t i = 0; i < adjList.size(); i++) {	// vertical, source
        for (size_t j = 0; j < adjList[i].size(); j++) {	// horizontal, destination
            int srcIdx = adjList[i][j]->source->vecIndex;
            int destIdx = adjList[i][j]->dest->vecIndex;
            dist[srcIdx][destIdx] = computeDist(adjList[i][j]->source, adjList[i][j]->dest);
        }
    }
    //std::cout << "start compute" << std::endl;
    for (int k = 0; k < adjSize; k++) {
        for (int i = 0; i < adjSize; i++) {	// source
            for (int j = 0; j < adjSize; j++) {	// destination
				// if k is on the shortest path from i to j, update the value of that path
                if ((dist[i][k] != std::numeric_limits<double>::max() && dist[k][j] != std::numeric_limits<double>::max()) && dist[i][j] > (dist[i][k] + dist[k][j])) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
	// print the shortest distance matrix
    std::fstream outputFS(fileName, std::fstream::out | std::fstream::trunc);
    std::stringstream line;
    if (writeToFile) {
        line << "    ";
        for (int i = 0; i < adjSize; i++) {
            line << id_to_Node(i)->abbr << " ";
        }
        line << std::endl;
        for (int i = 0; i < adjSize; i++) {
            line << id_to_Node(i)->abbr << " ";
            for (int j = 0; j < adjSize; j++) {
                if (dist[i][j] == std::numeric_limits<double>::max()) {
                    line << "INF ";
                }
                else {
                    line << dist[i][j] << " ";
                }
            }
            line << std::endl;
        }
    outputFS << line.str();    
    } else {
        printfloydWaSolution(dist);
    }
    outputFS.close();
}

/**
 * Compute the shortest path between start and destination airports via A* algorithms
 * @param string the start airport abbr
 * @param string the destination airport abbr
 */
void Graph::AStar(string start, string dest){
    cout << "\nSTART ASTAR SHORTEST PATH SEARCH" << endl;
    cout << "==========================================" << endl;
    
    //find the nodes base on the abbreviation
    Node *begin = abbr_to_Node(start);
    Node *end = abbr_to_Node(dest);
    
    unordered_map<Node*, double> distanceTo; //keep track of the cost
    unordered_map<Node*, Node*> parent; //keep track of the previous node of the current node

    //initialized the map
    for(auto it = idNodeMap.begin(); it != idNodeMap.end(); it++){
        distanceTo.insert({(*it).second,  std::numeric_limits<double>::max()}); 
        parent.insert({(*it).second, nullptr}); 
    }
    //set start and compute
    distanceTo[begin] = 0.0;
    //compute the fscore = the cost to reach this node + the heuristic (heuristic is the great circle distance) 
    begin->fscore = computeDist(begin, end);
    //customized priority queue to put the to-be-visited Nodes in order
    //the order: smallest fscore -----> largest fscore
    priority_queue<Node*, vector<Node*>, Comparator> pq;
    //insert the begin Node
    pq.push(begin);
    while(!pq.empty()){
        Node * current = pq.top();
        pq.pop();
        //cout << "start to dest: " << current->fscore << endl;
        if(current == end){
            break;
        }
        //go through all the adjacent nodes
        for(Edge * edge : adjList[current->vecIndex]){
            //this is the cost from current node to each adjacent node
            double distance = distanceTo[current] + computeDist(current, edge->dest);
            //compute the fscore for the adjacent nodes
            edge->dest->fscore = distance + computeDist(edge->dest, end);
            //update the cost of each adjacent node if the current cost is less
            if (distance < distanceTo[edge->dest]){
                distanceTo[edge->dest] = distance;
                parent[edge->dest] = current;
                pq.push(edge->dest);
            }
        }
    }
    //cout << "Distance from start (" << start << ") to dest ("<< dest << "): " << computeDist(begin,end) << endl;
    //To retrieve the path
    std::vector<Node*> res;
    Node * curr = end;
    while (curr != nullptr){
        res.insert(res.begin(), curr);
        curr = parent[curr]; 
    }
    nodeList = res;
    cout << "Job done" << endl;
    
    //for testing purpose it is included
    //printDetail();
}

/**
 * Print the detailed A* running result to the terminal
 */
void Graph::printDetail(){
    if(nodeList.size() < 2){ //there is only one airport
        cout << "Flight does not exists" << endl; 
        return;
    }
    double total_Distance = 0;
    //cout << "start to start: " << distanceTo[begin] << endl;
    for(size_t i = 0; i < nodeList.size()-1; ++i){
        double temp = computeDist(nodeList[i], nodeList[i+1]);
        total_Distance += temp;
    }
    cout << "The Total Distance is: " << total_Distance << " m " << endl;
    cout << "==============PATH============" <<endl;
    pathString.clear();
    for(Node * n: nodeList){
        pathString = pathString + " ---> " + n->abbr;
        cout << " ---> " << n->abbr; 
    }
    cout << "\n" << endl;
}

/**
 * Get the stored path string
 * @return the stored path string parameter
 */
std::string Graph::getPath(){
    return pathString;
}

/**
 * Print the detailed A* running result to a file
 * @param string the output file name
 */
void Graph::printDetailToFile(std::string fileName){
    if(nodeList.size() < 2){ //there is only one airport
        cout << "Flight does not exists" << endl; 
        return;
    }
    
    std::ofstream outputFile(fileName);
    if(outputFile.is_open()){
        double total_Distance = 0;
        //cout << "start to start: " << distanceTo[begin] << endl;
        for(size_t i = 0; i < nodeList.size()-1; ++i){
            double temp = computeDist(nodeList[i], nodeList[i+1]);
            total_Distance += temp;
        }
        outputFile << "The Total Distance is: " << total_Distance << " m " << endl;
        outputFile << "==============PATH============" <<endl;
        pathString.clear();
        for(Node * n: nodeList){
            outputFile << " ---> " << n->abbr; 
        }
        outputFile << "\n" << endl;
    }
    outputFile.close();
}
