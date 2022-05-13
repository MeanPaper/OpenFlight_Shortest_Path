#include "parseGraph.h"

/**
 * Helper function to delimit a given string with a delimiter
 * @return A vector of substrings being delimited
 * @param str_ A given string
 * @param delimiter A given delimiter
 */
vector<string> parseGraph::delimit(string str_, string delimiter) {
    std::vector<std::string> res;
    size_t pos_start = 0;
    size_t pos_end = delimiter.length();
    std::string token;

    while ((pos_end = str_.find(delimiter, pos_start)) != string::npos) {
        if (pos_start > 0 && isalpha(str_.at(pos_start - 2)) && str_.at(pos_start) == ' ') {
            pos_start = pos_end + delimiter.length();
            continue;
        } else {
            token = str_.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delimiter.length();
            res.push_back(token);
        }
    }
    res.push_back(str_.substr(pos_start));
    return res;
}

/**
 * A function to parse the input airport / route stream to an Adjacency List Graph
 * @param g A given graph
 * @param str_ input airport stream
 * @param delimiter input airport route stream
 */
void parseGraph::parseCSV(Graph &g, std::ifstream &airport_ifs, std::ifstream &route_ifs) {
    std::string line, tmp;
    int vecIndex = 0;
    if (airport_ifs.is_open()) {
        while (std::getline(airport_ifs, line)) {
            std::vector<std::string> vec = delimit(line, ",");
            string airportName = vec[1];
            airportName = airportName.substr(1,airportName.size()-2);
            string airportAbbr;
            if (vec[4] == "\\N") {
                airportAbbr = vec[5];
            } else {
                airportAbbr = vec[4];
            }
            airportAbbr = airportAbbr.substr(1, airportAbbr.size() - 2);
            double lat = stod(vec[6]);
            double lon = stod(vec[7]);               
            
            Graph::Node *n = new Graph::Node(vecIndex, lat, lon, airportName, airportAbbr);
            vecIndex += 1;
            g.addNode(n);
        }
    }
    if (route_ifs.is_open()) {
        while(std::getline(route_ifs, line)) {
            std::vector<std::string> vec = delimit(line, ",");
            std::string source = vec[2];
            std::string dest = vec[4];
            if (g.exists(source) && g.exists(dest)){
                Graph::Node* srcNode = g.abbr_to_Node(source);
                Graph::Node* destNode = g.abbr_to_Node(dest);
                Graph::Edge *e = new Graph::Edge(srcNode, destNode);
                g.addEdge(e);
            }
            else{
                g.increment_delete_flights();
            }
        }
    }
}
