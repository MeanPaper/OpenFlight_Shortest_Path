# Final Project Proposal
## 1. Leading Question
Airline route planning has been a classic problem since people want to save time on traveling. Our team is interested in dealing with airline route planning using several classic graph algorithms (BFS/ A\* algorithm\Floyd–Warshall), and flight and airport data from openflight. Specifically, we have 2 goals:

1. We want to find the shortest path between any two arbitrary airports. We will use A\* algorithm to solve the problem.
2. We want to produce shortest paths between all pairs of airports in our graph. We will use Floyd–Warshall algorithm to tackle this goal. 

## 2. Dataset Acquisition and Processing

1. **Data format** 
- We plan to use openflight (https://openflights.org/data.html) as our data source (csv format; 247 kb). The total number of airports is 7698, the total number of flights 67663. This means that we will have 7698 nodes, and 67663 edges. We will use part of the dataset, including the airport names,  locations, and possible flight routes. We define the airports as our graph nodes, possible routes as graph edges, and distances as our graph's edge cost.

2. **Data Correction**
- After downloading the CSV file, we will create a convertCSV function to parse airports as graph nodes, and all possible routes as graph edges. For route distances, we will use great circle distance to calculate them via airports' longitudes and latitudes.
- If there is any missing entry in our dataset (e.g., openflight says there is no flight between two airports, but it exists),  we will validate and append it. Our function will check for outliers/errors in our dataset/computation. If there is an error in our dataset (e.g., the longitude/ latitude data is out of range), we will do manual correction by searching online.

3. **Data Storage**
- We will use adjacency list to store our graph. We will treat it as an undirected weighted graph. 
- Space complexity: O(V+E) where V is the number of airports and E is the number of possible flight routes. In the worst case, our adjacency list implementation will be O(V<sup>2</sup>) when every node is connected to all other nodes. 

## 3. Graph Algorithm
1. **Graph Traversal: BFS** 
	* Description: Using the BFS traversal algorithm, we can find the shortest path that contains the least number of intermediate nodes between our origin and destination airports.
	* Input: 2 arbitrary airports as the origin and the destination.  
   * Output: the shortest path between the two airports based on the number of intermediate nodes. 
   * Run time complexity: O(V+E) where V is the number of airports and E is the number of routes.
   * Space complexity:  O(V) where V is the number of airports
2. **A\* Algorithm**
	* Description: A\* algorithm can find the shortest path (with the shortest distance) between our origin and destination. It is more efficient than Dijkstra's algorithm due to heuristics. We plan to use the great circle distance as our A\* heuristics.
   * Input: 2 arbitrary airports as the start point and the destination. 
   * Output: the shortest path between the two airports based on the shortest distance. 
   * Run time complexity: O(ElogV) using a minimum priority queue if we consider our heuristics is O(1).
   * Space complexity:  O(V) where V is the number of airports.
3. **Floyd–Warshall algorithm**
	* Description: Floyd–Warshall algorithm is great for solving shortest path problem for all pairs of airports in our graph.
	* Input: the graph containing all airports and routes
   * Output: the shortest path between the all pairs of airports based on the shortest distance. 
   * Run time complexity: O(V<sup>3</sup>) where V is the number of airports
   * Space complexity:  O(V<sup>2</sup>) where V is the number of airports

## 4. Timeline
| Time        | Description                                                  |
| ----------- | ------------------------------------------------------------ |
| Before 3/25 | Submit team contract and proposal                            |
| 3/26- 4/1   | Data acquisition and data preprocessing; design the class diagram/project architecture |
| 4/2 - 4/15   | Complete the BFS algorithm and the A\* algorithm; write tests to prove algorithm works  |
| 4/16 - 4/22 | Complete the Floyd–Warshall Algorithm; write tests to prove the algorithms worked |
| 4/23 - 4/29 | write tests to verify the algorithms worked; wrap up our code |
| 4/30 - 5/6  | work on presentation; submit the project deliverables |

