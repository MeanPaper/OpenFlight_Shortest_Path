# Development Log

## Week(3/28 - 4/1)
### Goal: 
- Parse the csv files from openflight to construct a graph
- Test the parsed data stored in the graph
- Design the overall project architecture
- Write a simple implementation of Dijkstra's algorithm
### Progress:
All team members finished their designated tasks successfully.
- Revised Team Proposal based on the provided feedback (the team)
- Finished collecting all the airports and flights informations and stored the information in two `.dat` files (one for airports and the other for flights) (Han Xu)
- Tested that the parsed data in the graph correspond to the airport full name, airport abbreviation, airport longitude and latitude (Owen Xu)
- Completed the following functionalities:
  - Handling file input (Han Xu)
  - Constructing graph vertices and edges based on the airports and flights information from the files. (Dongmin Liu, Han Xu)
  - Constructing graph (Dongmin Liu, Han Xu)
  - Finding the shortest path using a simple and unoptimized Dijkstra's algorithm (Dongmin Liu)
  - Outputting the path information on terminal (Owen Xu)
- Designed the project architecture by drawing the class diagram (Carl Xu) 
### Problems encountered:
A couple of airports's longitude/latitude data were incorrect. We corrected them according to online information. Several airports existed in the routes were not present in our airports dataset, our team discussed and decided to remove those routes.

### Plan for next week:
At this point, our codes can run and pass simple cases. We will do more unit testing and optimization to ensure that the code is running quickly and safely for next week. We also plan to finish 50% of BFS algorithm. 

## Week(4/2 - 4/8)
### Goal: 
- Meet with team mentor and revise Proposal according to the mentor's suggestions
- Finish 50% of the BFS algorithm; work on BFS's test cases
- Finish 50% of the A* algorithm
- Look into Floyd-Warshall algorithm
### Progress:
All team members finished their designated tasks successfully.
- Meet with Mentor to discuss modifications to the Proposal. (Han Xu)
- Revised Team Proposal based on the provided feedback (the team)
- Finished 50% of the BFS algorithm. (Han Xu)
- Wrote test cases for the BFS algorithm. (Owen Xu)
- Finished 50% of the A* algorithm. (Dongming Liu)
- Read papers and resources regarding Floyd-Warshall algorithm. (Carl Xu)
### Problems encountered:
There are some issues with current A* algorithm. 
- The code of A* algorithm runs into infinite loop
- The code only construct some parts of the shortest path between two points

We plan to address these issues next week

### Plan for next week:
We will wrap up BFS and A* algorithm next week. We will do more tests to ensure that the code efficient and robust. We also plan to start working on Floyd–Warshall Algorithm.


## Week(4/9 - 4/15)
### Goal: 
- Finish A* Algorithm and testcases;
- Finish BFS Algorithm and testcases;
- Write more testcase to prove that the input of data is correct. 
- Finish 30% of Floyd-Warshall Algorithm. 

### Progress:
All team members finished their designated tasks successfully.

- Finished the BFS algorithm. (Han Xu)
- Wrote test cases for the algorithms and check for the accuracy of input data. (Owen Xu)
- Finished the A* algorithm. (Dongming Liu)
- Started to working on Floyd-Warshall method and finished 30% of it. (Carl Xu)

### Problems encountered:
- The number of edges does not match with the number of flights from the datasheet. This is because when we  input flights into the graph as edges, we remove those flights which has no starting/ending airports abbreviation name. After adding the number of deleted flights, our number of edges matches with the datasheet. So the input of the data is all correct. 

### Plan for next week:
We will finish writing the Floyd-Warshall Algorithm and write testcases for it. And on April 22nd 1:00PM, we will meet with the mentor to do the mid-project check-in. 


## Week(4/16 - 4/22)
### Goal: 
- Refine A* testcases;
- Refine BFS testcases;
- Refine parsing testcases. 
- Finish 80% Floyd-Warshall Algorithm;
- Finish mid-project check-in;

### Progress:
All team members finished their designated tasks successfully.

- Finished the A* algorithm; (Dongming Liu)
- Refine BFS testcases; (Han Xu)
- Refine parsing testcases; (Han Xu and Owen Xu)
- Finish 80% Floyd-Warshall Algorithm; (Carl Xu)
- Finish mid-project check-in; (Team)

### Problems encountered:
- A* cannot find path for medium-size testcases, we plan to solve it next week. 

### Plan for next week:
Refine all testcases and algorithms. Finish Floyd-Warshall. 



## Week(4/23 - 4/29)

### Goal: 

- Correct A* algorithm and refine the testcases;
- Finish 90% Floyd-Warshall Algorithm;
- Discussed the exact plan for our final week, including presentation/readme.md/report

### Progress:

All team members finished their designated tasks successfully.

- Correct A* algorithm and refine the testcases; (Dongming Liu, Han Xu and Owen Xu)
- Finish 90% Floyd-Warshall Algorithm; (Carl Xu)
- Planned for our final week, including presentation/readme.md/report; (Team)

### Problems encountered:

- Had some issue with the understanding of C++ comparator; corrected the C++ comparator after referring to online tutorials
- Corrected Git repo issue ("accidentally included a Git repo in the current branch")

### Plan for next week:

Refine all testcases and algorithms. Finished our presentation/readme.md/report and do our submission.


## Week(4/30 - 5/6)

### Goal: 

- Complete all test cases.
- Finish Floyd-Warshall Algorithm;
- Complete a console-based user interface to compute for our goals / conduct test cases.
- Finish the video presentation / written report(results.md) / descriptive README.

### Progress:

All team members finished their designated tasks successfully.

- Completed all test cases; (Dongming Liu, Han Xu and Owen Xu)
- Finished Floyd-Warshall Algorithm; (Carl Xu)
- Completed a console-based user interface to compute for our goals / conduct test cases; (Dongming Liu)
- Finished the video presentation / written report(results.md) / descriptive README. (Team)

### Problems encountered:

- Had some issue with Floyd-Warshall since the pseudo code uses Adjacency Matrix; modified the algorithm with respect to our adjacency list representation of graph

### Plan for next week:

- None since we are done for the project.