#include "Test.h"

/**
 * Compares whether two given files are the same
 * Reference: https://stackoverflow.com/a/37575457
 * @return return true if two files are the same
 * @param p1 file location for the 1st file
 * @param p2 file location for the 2nd file
 */
bool Test::compareFiles(const std::string& p1, const std::string& p2) {
  std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
  std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

  if (f1.fail() || f2.fail()) {
    return false; //file problem
  }

  if (f1.tellg() != f2.tellg()) {
    return false; //size mismatch
  }

  //seek back to beginning and use std::equal to compare contents
  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);
  return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f2.rdbuf()));
}

/**
 * Validate whether the parsed graph has 7697 nodes (airports).
 * @param g The parsed graph
 */
void Test::validateNodeNo(Graph g){
    if(g.nodeNumber() != 7697){
        std::cout<<"test for number:" << g.nodeNumber()<<endl;
    }
    else{
        std::cout<<"The number of nodes (airports) is: " <<g.nodeNumber()<<", which is correct"<<endl;
    }
}

/**
 * Checks whether the airport abbreviation exists in the original dataset
 * @return return true if an airport exists / returns false if the airport does not exist
 * @param abbr airport abbreviation
 */
bool Test::checkAiportExists(std::string abbr){
    std::ifstream airport_ifs("../data/airports.dat");
    std::string line;
    for(unsigned int curLine = 0; getline(airport_ifs, line); curLine++) {
        if (line.find(abbr) != string::npos) {
            return true;
        }
    }
    return false;
}

/**
 * checks whether a the graph's nodes are valid
 * @param g a parsed graph
 */
void Test::validateNodeWithFile(Graph g){
    std::unordered_map<std::string, Graph::Node*> abbrMap = g.getAbbrMap();
    std::cout << "map size:" << abbrMap.size() << std::endl;
    bool wrong = false;
    for (const auto &myPair: abbrMap) {
        if (!checkAiportExists(myPair.first)) {
            std::cout << "cannot find: " << myPair.first << std::endl;
            wrong = true;
        }
    }
    if (wrong) {
        std::cout << "not all airports match with what inside source file" << std::endl;
    }
    else {
        std::cout << "all airports match with what inside source file" << std::endl;
    }
}

/**
 * checks whether the graph's edge exists in the original dataset
 * @return return true if the edge exists / return false if the edge does not exist
 * @param start the start airport
 * @param end the destination airport
 */
bool Test::checkEdgeExists(std::string start, std::string end){
    std::ifstream airport_ifs1("../data/route.dat");
    std::ifstream airport_ifs2("../data/route.dat");
    std::unordered_set<int> set1, set2;
    std::string line;
    for(unsigned int curLine = 0; getline(airport_ifs1, line); curLine++) {
        if (line.find(start) != string::npos) {
            set1.insert(curLine);
        }
    }
    for(unsigned int curLine = 0; getline(airport_ifs2, line); curLine++) {
        if (line.find(end) != string::npos) {
            set2.insert(curLine);
        }
    }
    //check whether two line idx equal
    for (int idx:set1) {
        if (!set2.count(idx)) {
            return false;
        }
    }
    return true;
}

/**
 * checks whether a the graph's edges are valid with respect to the source dataset
 * @param g a parsed graph
 */
void Test::validateEdgeWithFile(Graph g){
    std::vector<std::vector<Graph::Edge *>> edgeVec = g.getAdjList();
    bool wrong = false;
    for (size_t i = 0; i < edgeVec.size(); i++) {
        for (auto e:edgeVec[i]) {
            if (!checkEdgeExists(e->source->abbr, e->dest->abbr)) {
                wrong = true;
            }
        }
    }
    if (wrong) {
        std::cout << "not all edges match with what inside source file" << std::endl;
    }
    else {
        std::cout << "all edges match with what inside source file" << std::endl;
    }
}

/**
 * Validate whether the parsed graph has 67663 edges (distinct flight iternrary).
 * @param g The parsed graph
 */
void Test::validateEdgeNo(Graph g){
    if(g.edgeCount + g.delete_flights != 67663){
        cout<<g.edgeCount<<endl;
        cout<<"number of input flights is not correct"<<endl;
    }
    else{
        cout<<"Number of flights is: "<<g.edgeCount<<", which is correct"<<endl;
    }
}

/**
 * Validate whether the parsed graph's contains lat/lon data, airport abbreviation that adhere to format.
 * @param g The parsed graph
 */
void Test::testParse(Graph g) {
    for(auto &it:g.all_node){
        //check lat / lon 
        if((it->lat) < -90.0 || (it->lat) > 90.0){
            std::cout<< it->abbr<<endl;
            std::cout<<" The entered lat is out of range" << endl;
        }

        if((it->lon) < -180.0 || (it->lon) > 180.0){
            std::cout<< it->abbr<<endl;
            std::cout<<" The entered lon is out of range" << endl;
        }
        // check obtained abbr
        if((it->abbr.size()>4 || it->abbr.size()<3) ){
            if(it->abbr.size() != 0){
                std::cout << it->abbr << endl;
                //std::cout << it->name << endl;
                std::cout<<"The above abbr is not valid"<<endl; 
            }
                          
        } 

        for(size_t i = 0; i < it->abbr.size(); i++){
            if(!isupper(it->abbr[i]) && ! isdigit(it->abbr[i])){
                std::cout<< it->abbr<<endl;
                std::cout<<"The entered abbr is not valid"<<endl; 
            }
        }
        // //check name
        // for(int i =0;i < it->name.size();i++){
        //     if(!isalpha(it->name[i]) && it->name[i] != ' ' && it->name[i] != '/'&& it->name[i] != '\\'&& it->name[i] != '~'&& it->name[i] != '\''&& it->name[i] != '-'){
        //         std::cout<<it->name[i]<< std::endl;
        //         std::cout<< it->name<< std::endl;
        //         std::cout<<"The entered name is not valid"<< std::endl;
        //         break;
        //     }
        // } // suppose the condition is right. 
    }
}

/**
 * BFS test case 1 running on a small graph
 */
void Test::testBFSSmall1(){
    Graph g;
    parseGraph parser;

    std::string airportTest = "../data/airports_test_small.dat";
    std::string routesTest = "../data/routes_test_small.dat";
    std::ifstream airport_ifs_test(airportTest);
    std::ifstream route_ifs_test(routesTest);

    parser.parseCSV(g, airport_ifs_test, route_ifs_test);
    g.BFS("AER", "KZN", true, "bfs_small_1.txt");
    if (compareFiles("../tests/bfs_small_1_sol.txt", "bfs_small_1.txt")) {
        std::cout << "test BFS Small 1 succeeded." << std::endl;
    } else {
        std::cout << "test BFS Small 1 failed." << std::endl;
    }    
}

/**
 * BFS test case 2 running on a small graph
 */
void Test::testBFSSmall2(){
    Graph g;
    parseGraph parser;

    std::string airportTest = "../data/airports_test_small.dat";
    std::string routesTest = "../data/routes_test_small.dat";
    std::ifstream airport_ifs_test(airportTest);
    std::ifstream route_ifs_test(routesTest);

    parser.parseCSV(g, airport_ifs_test, route_ifs_test);   
    g.BFS("ASF", "KZN", true, "bfs_small_2.txt");
    if (compareFiles("../tests/bfs_small_2_sol.txt", "bfs_small_2.txt")) {
        std::cout << "test BFS Small 2 succeeded." << std::endl;
    } else {
        std::cout << "test BFS Small 2 failed." << std::endl;
    }        
}

/**
 * BFS test case 3 running on a small graph
 */
void Test::testBFSSmall3(){
    Graph g;
    parseGraph parser;

    std::string airportTest = "../data/airports_test_small.dat";
    std::string routesTest = "../data/routes_test_small.dat";
    std::ifstream airport_ifs_test(airportTest);
    std::ifstream route_ifs_test(routesTest);

    parser.parseCSV(g, airport_ifs_test, route_ifs_test);   
    g.BFS("ASF", "MRV", true, "bfs_small_3.txt");
    if (compareFiles("../tests/bfs_small_3_sol.txt", "bfs_small_3.txt")) {
        std::cout << "test BFS Small 3 succeeded." << std::endl;
    } else {
        std::cout << "test BFS Small 3 failed." << std::endl;
    }            
}

/**
 * BFS test case running on a medium-sized graph
 */
void Test::testBFSMed(){
    Graph g;
    parseGraph parser;

    std::string airportTest = "../data/airports_test_med.dat";
    std::string routesTest = "../data/routes_test_med.dat";
    std::ifstream airport_ifs_test(airportTest);
    std::ifstream route_ifs_test(routesTest);

    parser.parseCSV(g, airport_ifs_test, route_ifs_test);
    g.BFS("LAX", "BKK", true, "bfs_med_1.txt");
    if (compareFiles("../tests/bfs_med_1_sol.txt", "bfs_med_1.txt")) {
        std::cout << "test BFS Med succeeded." << std::endl;
    } else {
        std::cout << "test BFS Med failed." << std::endl;
    }           
}

/**
 * BFS test case running on a large graph (the original complete dataset)
 */
void Test::testBFSLarge(){
    Graph g;
    parseGraph parser;

    std::string airportTest = "../data/airports.dat";
    std::string routesTest = "../data/routes.dat";
    std::ifstream airport_ifs_test(airportTest);
    std::ifstream route_ifs_test(routesTest);

    parser.parseCSV(g, airport_ifs_test, route_ifs_test);
    g.BFS("LAX", "BKK", true, "bfs_large_1.txt");
}

/**
 * A* test case running on a small graph
 */
void Test::AstarTestSmall(){
    Graph g;
    parseGraph parser;
    cout << "\n============== Astar Test Small =================\n";
    std::string airportTest = "../data/airports_test_small.dat";
    std::string routesTest = "../data/routes_test_small.dat";
    std::ifstream airport_ifs_test(airportTest);
    std::ifstream route_ifs_test(routesTest);

    parser.parseCSV(g, airport_ifs_test, route_ifs_test);
    g.AStar("AER", "KZN");
    g.printDetailToFile("Astar_test_small_1.txt");
    g.AStar("ASF", "KZN");
    g.printDetailToFile("Astar_test_small_2.txt");
    g.AStar("ASF", "MRV");
    g.printDetailToFile("Astar_test_small_3.txt");

    if (compareFiles("../tests/Astar_test_small_1_sol.txt", "Astar_test_small_1.txt")) {
        std::cout << "test Astar Small 1 succeeded." << std::endl;
    } else {
        std::cout << "test Astar Small 1 failed." << std::endl;
    }          
    if (compareFiles("../tests/Astar_test_small_2_sol.txt", "Astar_test_small_2.txt")) {
        std::cout << "test Astar Small 2 succeeded." << std::endl;
    } else {
        std::cout << "test Astar Small 2 failed." << std::endl;
    }          
    if (compareFiles("../tests/Astar_test_small_3_sol.txt", "Astar_test_small_3.txt")) {
        std::cout << "test Astar Small 3 succeeded." << std::endl;
    } else {
        std::cout << "test Astar Small 3 failed." << std::endl;
    }          
}

/**
 * A* test case running on a medium-sized graph
 */
void Test::AstarTestMedium(){
    Graph g;
    parseGraph parser;
    cout << "\n============== Astar Test Medium =================\n";
    std::string airportTest = "../data/airports_test_med.dat";
    std::string routesTest = "../data/routes_test_med.dat";
    std::ifstream airport_ifs_test(airportTest);
    std::ifstream route_ifs_test(routesTest);

    parser.parseCSV(g, airport_ifs_test, route_ifs_test);
    g.AStar("LAX", "BKK");
    g.printDetailToFile("Astar_test_medium_1.txt");
    if (compareFiles("../tests/Astar_test_medium_1_sol.txt", "Astar_test_medium_1.txt")) {
        std::cout << "test Astar Medium 1 succeeded." << std::endl;
    } else {
        std::cout << "test Astar Medium 1 failed." << std::endl;
    }    
}

/**
 * A* test case running on a large graph (the original complete dataset)
 */
void Test::AstarTest(){
    Graph g;
    parseGraph parser;
     cout << "\n============== Astar Test Entire Data Set =================\n";
    std::string airportTest = "../data/airports.dat";
    std::string routesTest = "../data/routes.dat";
    std::ifstream airport_ifs_test(airportTest);
    std::ifstream route_ifs_test(routesTest);

    parser.parseCSV(g, airport_ifs_test, route_ifs_test);
    g.AStar("LAX", "BKK");
    g.printDetailToFile("Astar_test_whole.txt");
    g.AStar("CAN", "ORD");
    g.printDetailToFile("Astar_test_whole_2.txt");

    if (compareFiles("../tests/Astar_test_whole_sol.txt", "Astar_test_whole.txt")) {
        std::cout << "test Astar whole succeeded." << std::endl;
    } else {
        std::cout << "test Astar whole failed." << std::endl;
    }
    if (compareFiles("../tests/Astar_test_whole_2_sol.txt", "Astar_test_whole_2.txt")) {
        std::cout << "test Astar whole 2 succeeded." << std::endl;
    } else {
        std::cout << "test Astar whole 2 failed." << std::endl;
    }             
}

/**
 * Floyd Warshall test case running on a small-sized graph
 */
void Test::testFloydWarshallSmall(){
    Graph g;
    parseGraph parser;    
    std::string airportTest = "../data/airports_test_small.dat";
    std::string routesTest = "../data/routes_test_small.dat";
    std::ifstream airport_ifs_test(airportTest);
    std::ifstream route_ifs_test(routesTest);

    parser.parseCSV(g, airport_ifs_test, route_ifs_test);
    g.floydWarshall(true, "floyd_small_output.txt");
    if (compareFiles("../tests/floyd_small_sol.txt", "floyd_small_output.txt")) {
        std::cout << "testFloydWarshallSmall succeeded." << std::endl;
    } else {
        std::cout << "testFloydWarshallSmall failed." << std::endl;
    }
}

/**
 * Floyd Warshall test case running on a medium-sized graph
 */
void Test::testFloydWarshallMed(){
    Graph g;
    parseGraph parser;    
    std::string airportTest = "../data/airports_test_med.dat";
    std::string routesTest = "../data/routes_test_med.dat";
    std::ifstream airport_ifs_test(airportTest);
    std::ifstream route_ifs_test(routesTest);

    parser.parseCSV(g, airport_ifs_test, route_ifs_test);
    g.floydWarshall(true, "floyd_med_output.txt");
    if (compareFiles("../tests/floyd_med_sol.txt", "floyd_med_output.txt")) {
        std::cout << "testFloydWarshallMed succeeded." << std::endl;
    } else {
        std::cout << "testFloydWarshallMed failed." << std::endl;
    }    
}

/**
 * Floyd Warshall test case running on a large graph (the original complete dataset)
 * Note: it takes ~1.5 hours to run it our original dataset is huge and Floyd Warshall is O(V^3) run-time complexity
 * Note: we comment it out since it takes too long to run
 */
void Test::testFloydWarshallLarge(){
    Graph g;
    parseGraph parser;    
    std::string airportTest = "../data/airports.dat";
    std::string routesTest = "../data/routes.dat";
    std::ifstream airport_ifs_test(airportTest);
    std::ifstream route_ifs_test(routesTest);

    parser.parseCSV(g, airport_ifs_test, route_ifs_test);
    //g.floydWarshall(true, "floyd_large_output.txt");
    // if (compareFiles("../tests/floyd_med_sol.txt", "floyd_large_output.txt")) {
    //     std::cout << "testFloydWarshallMed success." << std::endl;
    // } else {
    //     std::cout << "testFloydWarshallMed fails." << std::endl;
    // }
}