#include "user.h"

using namespace std;

/**
 * A function that handles the user interaction inside the terminal
 * 4 options: option 1: run A* for 2 arbitrary airports
 *            option 2: run all test cases
 *            option 3: run Floyd-Warshall on entire dataset
 *            option 4: run BFS for 2 arbitrary airports
 * @param flightMap A pointer to a graph of airports and routes
 */
void userInteraction(Graph * flightMap){
    int mode;
    char choice;
    string starting;
    string destination;
    string tempFileName;
    while(1){
        //intro
        cout << "Welcome, please select your mode: " << endl;
        cout << "1. Input Start and Destination [Enter 1]" <<endl;
        cout << "2. Run All Test Cases [Enter 2]" <<endl;
        cout << "3. Run Floyd-Warshall on the entire data set [Enter 3]" << endl;
        cout << "4. Run BFS on the entire data set [Enter 4]" << endl;
        cout << "WARNING: Option 3 will take approximately 1 and a half hour to run" << endl;
        cout << "because the runtime of Floyd-Warshall is O(V^3)" << endl;

        //get the mode selection
        ModeInput: cin >> mode; 
        if(cin.fail() || mode < 1 || mode > 4){ //mode input validation
            cout << "Please enter a valid integer" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto ModeInput;
        }
        
        //mode 1 is chosen
        if(mode == 1){
            cout << "Mode 1 " << endl; //mode 1 here
            
            StartAirport: //label
            cout << "From [Your Starting Airport Abbreviation]: ";
            
            if(cin >> starting){ //starting point input validation
                //cout << starting.size();
                if(!flightMap->exists(starting)){ //check if the airport exists
                    cout << "\nAirport Abbreviation Invalid or Airport Does Not Exist! Try Again!" << endl;
                    goto StartAirport; 
                }
            }
            else{ //prevent user to input something illegal
                cout << "Please enter a valid Airport Abbreviation" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto StartAirport; 
            }
            
            EndAirport: //label
            cout << "To [Your Destination Airport Abbreviation]: ";
            
            if(cin >> destination){ //ending point input validation
                if(!flightMap->exists(destination)){ //check if the airport exists
                    cout << "\nAirport Abbreviation Invalid or Airport Does Not Exist! Try Again!" << endl;
                    goto EndAirport;
                }
            }
            else{//prevent user to input something illegal
                cout << "Please enter a valid Airport Abbreviation" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto EndAirport;
            }
            
            //the following code will be called if all the data are valid
            //using Astar to find the shortest path
            auto start = std::chrono::high_resolution_clock::now();
            flightMap->AStar(starting, destination);    
            auto end = std::chrono::high_resolution_clock::now();
            //printing the detail of the shortest path
            flightMap->printDetail();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);   
            std::cout << "Time taken by A* algorithm: " << duration.count() << " ms" << std::endl;
        }
        else if (mode == 2) {
            Test test;
            // test the parsed graph
            test.testParse(*flightMap);
            test.validateNodeNo(*flightMap);
            test.validateEdgeNo(*flightMap);
            // test.validateNodeWithFile(*flightMap);
            // test.validateEdgeWithFile(*flightMap);            
            test.testFloydWarshallSmall();
            test.testFloydWarshallMed();
            test.testFloydWarshallLarge();
            
            //test BFS
            test.testBFSSmall1();
            test.testBFSSmall2();
            test.testBFSSmall3();
            test.testBFSMed();
            test.testBFSLarge();
            
            //test astar
            test.AstarTestSmall();
            test.AstarTestMedium();
            test.AstarTest();            
        }
        else if(mode == 4){
            cout << "Mode 4 " << endl; //mode 4 here
            
            StartAirport_: //label
            cout << "From [Your Starting Airport Abbreviation]: ";
            
            if(cin >> starting){ //starting point input validation
                //cout << starting.size();
                if(!flightMap->exists(starting)){ //check if the airport exists
                    cout << "\nAirport Abbreviation Invalid or Airport Does Not Exist! Try Again!" << endl;
                    goto StartAirport_; 
                }
            }
            else{ //prevent user to input something illegal
                cout << "Please enter a valid Airport Abbreviation" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto StartAirport_; 
            }
            
            EndAirport_: //label
            cout << "To [Your Destination Airport Abbreviation]: ";
            
            if(cin >> destination){ //ending point input validation
                if(!flightMap->exists(destination)){ //check if the airport exists
                    cout << "\nAirport Abbreviation Invalid or Airport Does Not Exist! Try Again!" << endl;
                    goto EndAirport_;
                }
            }
            else{//prevent user to input something illegal
                cout << "Please enter a valid Airport Abbreviation" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto EndAirport_;
            }
            
            //the following code will be called if all the data are valid
            //using Astar to find the shortest path
            auto start = std::chrono::high_resolution_clock::now();
            flightMap->BFS(starting, destination, false, "");    
            auto end = std::chrono::high_resolution_clock::now();
            //printing the detail of the shortest path
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);   
            std::cout << "Time taken by BFS algorithm: " << duration.count() << " ms" << std::endl;
        }
        else if(mode == 3){
            //print the entire graph to terminal
            flightMap->floydWarshall(false, "");
        }
        
        cout << "Do you want to exit the program? [y/n]" << endl;
        RESUME: cin >> choice;
        if(cin.fail()){ //choice validation
            cout << "Invalid Input, try again"<< endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto RESUME;
        }
        
        //choice check
        if(choice == 'y' || choice == 'Y'){ //choice for exiting the program
            cout << "Quit" << endl;
            break;
        }
        else if(choice == 'n' || choice == 'N'){ //choice for continuing the program
            cout << "Continue" << endl;
            continue;
        }
        else{
            cout << "Invalid Choice, try again"<< endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto RESUME;            
        }
    }
}
