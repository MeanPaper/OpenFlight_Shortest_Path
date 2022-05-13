#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "Graph.h"
#include "vector"
#include "Test.h"
#include "parseGraph.h"
#include <chrono>

/**
 * A function that handles the user interaction inside the terminal
 * 4 options: option 1: run A* for 2 arbitrary airports
 *            option 2: run all test cases
 *            option 3: run Floyd-Warshall on entire dataset
 *            option 4: run BFS for 2 arbitrary airports
 * @param flightMap A pointer to a graph of airports and routes
 */
void userInteraction(Graph * flightMap);
