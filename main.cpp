#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <time.h>
#include "problem.h"
#include "Node.h"
#include "custom_priority_queue.h"

using namespace std;

//url for the rest of the code is https://github.com/KiyomiS/CS170-8Puzzle
//https://stackoverflow.com/questions/876901/calculating-execution-time-in-c
//used to get time

Node * uniformSearch(problem * prb, vector<int> start_point);
Node * Astar_MisplacedTile(problem * prb, vector<int> start_point);
Node * Astar_ManhattanDistance(problem * prb, vector<int> start_point);

int main() {
    int option, searchOption;
    int input;
    vector<int>start(0);
    cout << "Welcome to my 170 8-Puzzle Solver. Type '1' to use a default puzzle, or '2' to create your own." << endl;
    cin >> option;
    if(option == 1) {
        start = {0, 7, 2, 4, 6, 1, 3, 5, 8};
    }
    if(option == 2){
        cout << "Enter your puzzle, using a zero to represent the blank. Please only enter valid 8-puzzles. Enter the puzzle with spaces in between each number." << endl;
        for(int i = 0; i < 9; i++){//take in the puzzle one integer at a time
            cin >> input;
            start.push_back(input);
        }
    }

//creation of the problem
    problem * start_game = new problem(start);
    Node * game_over = nullptr;
    Node* print_start = new Node(start, start.size());

    print_start->PrintState();

    
    cout << "Select search algorithm" << endl;
    cout << " Option 1: Uniform cost search\n Option 2: A* with the Misplaced Tile heuristic\n Option 3: A* with the Manhattan Distance heuristic" << endl;
    cin >> searchOption;
    cout << endl;

    clock_t tStart = clock();
    if(searchOption == 1){
        game_over = uniformSearch(start_game, start);
    } else if (searchOption == 2) {
        game_over = Astar_MisplacedTile(start_game, start);
    } else {
        game_over = Astar_ManhattanDistance(start_game, start);
    }
    cout << "Time taken was: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

    game_over->PrintState();
}

Node * uniformSearch(problem * prb, vector<int> start_point){
    unsigned long long numberofNodes = 0;
    unsigned long long depth = 0;
    custom_priority_queue<Node*, vector<Node*>, compareNodes> uniform_queue;
    Node* begin = new Node(start_point, start_point.size());
    long long qSize = 0;
    unsigned long long nodesExpanded = 0;
    vector<Node*> track(0); //keep track of all states
    vector<Node*> expandedSet(0); //keep track of all states that have already been expanded.
    uniform_queue.push(begin);
   
    while(!uniform_queue.empty()){
        if(uniform_queue.size() > qSize) {
            qSize = uniform_queue.size(); // keep track of queue size for output
        }

        Node * check = uniform_queue.top(); //taking the first node, at the beginning it will be the node passed in or default node
        
        if(track.empty()){
            track.push_back(check); // keep track of all different visited states so if we run into the same state we can compare costs.
        }
        //cout << expandedSet.size();
        // string in;
        // cin >> in;
        cout << "The best state to expand with g(n) = " << check->getCost() << " and h(n) = " << check->getHCost() << " is...." << endl;
        check->PrintState();

        uniform_queue.pop(); //remove node we are checking because we wont have to check it again since we're creating all of its children.
        if (check->getState() == prb->getGoal()){ //checking if we're at the goal state
            cout << "Goal state!" << endl << "Solution depth was: " << check->getCost() << endl;
            cout << "Number of nodes expanded: " << nodesExpanded << endl;
            cout << "Max queue size: " << qSize << endl;
            return check;
        }
        //not in goal state, check to expand nodes.
        depth++; // keep track of depth
        nodesExpanded++;
        expandedSet.push_back(check);

        for(int i = 0; i < 4; i++){ //have to check 4 operators
            if(prb->canDo(check, i)){ //if it is a valid move
                numberofNodes++; //keep track of number of nodes created
                Node* createChild = prb->Child(check, i); //create the child node

                bool istrue = false;
                for(int i = 0; i < expandedSet.size(); i++){ //looking to see state has already been expanded
                    // cout << "Checking" << endl;
                    //cout << "checking if state has been visited" << endl;
                    if(expandedSet[i]->getState() == createChild->getState()){ //if state is visited
                         istrue = true;
                    }
                }

                bool checktrack = false;
                for(int i = 0; i < track.size(); i++){ //looking to see state has already been visited
                    // cout << "Checking" << endl;
                    //cout << "checking if state has been visited" << endl;
                    if(track[i]== createChild){ //if state is visited
                         checktrack = true;
                    }
                }

                //cout << "done checking" << endl;
                if(!istrue) { //not an old expanded state, check if its in queue
                    cout << "adding node" << endl;
                    if(!uniform_queue.find(createChild)){ //if its not in the queue nor has it been expanded nor is it in track, basically a whole new state
                        uniform_queue.push(createChild); //add to queue
                        track.push_back(createChild); //add to track as well
                        //cout << "option" << endl;
                        //createChild->PrintState();
                    } else {
                        for(int i = 0; i < track.size(); i++) {
                            if(track[i]->getState() == createChild->getState()){ //find the one in the queue by looking through track
                                if(track[i]->getCost() < createChild->getCost()){ //check if node in track has less cost
                                    uniform_queue.push(track[i]); //if so add it instead of new child
                                    //delete createChild;
                                    //cout << "Option" << endl;
                                    //track[i]->PrintState();
                                } else {
                                    uniform_queue.remove(createChild);
                                    uniform_queue.push(createChild); //add new lower node
                                    track[i]->setCost(createChild->getCost()); //set the tracked nodes cost to lower of the two.
                                    //cout << "Option" << endl;
                                    //createChild->PrintState(); 
                                }
                            }
                        } 
                    }
                }                 
            }
        }
    }
    return nullptr;
}

Node * Astar_MisplacedTile(problem * prb, vector<int> start_point){
    unsigned long long numberofNodes = 0;
    unsigned long long depth = 0;
    custom_priority_queue<Node*, vector<Node*>, compareNodes> uniform_queue;
    Node* begin = new Node(start_point, start_point.size());
    unsigned long long nodesExpanded = 0;
    prb->misplacedTile(begin);
    long long qSize = 0;
    vector<Node*> track(0); //keep track of all states
    vector<Node*> expandedSet(0); //keep track of all states that have already been expanded.
    uniform_queue.push(begin);
   
    while(!uniform_queue.empty()){
        if(uniform_queue.size() > qSize) {
            qSize = uniform_queue.size(); // keep track of queue size for output
        }
        
        Node * check = uniform_queue.top(); //taking the first node, at the beginning it will be the node passed in or default node
        
        if(track.empty()){
            track.push_back(check); // keep track of all different visited states so if we run into the same state we can compare costs.
        }
        //cout << expandedSet.size();
        // string in;
        // cin >> in;
        cout << "The best state to expand with g(n) = " << check->getCost() << " and h(n) = " << check->getHCost() << " is...." << endl;
        check->PrintState();

        uniform_queue.pop(); //remove node we are checking because we wont have to check it again since we're creating all of its children.
        if (check->getState() == prb->getGoal()){ //checking if we're at the goal state
            cout << "Goal state!" << endl << "Solution depth was: " << check->getCost() << endl;
            cout << "Number of nodes expanded: " << nodesExpanded << endl;
            cout << "Max queue size: " << qSize << endl;
            return check;
        }
        //not in goal state, check to expand nodes.
        depth++; // keep track of depth
        nodesExpanded++;
        expandedSet.push_back(check);

        for(int i = 0; i < 4; i++){ //have to check 4 operators
            if(prb->canDo(check, i)){ //if it is a valid move
                numberofNodes++; //keep track of number of nodes created
                Node* createChild = prb->Child(check, i); //create the child node

                //call misplaced tile to calculate the H(n) for the new node.
                prb->misplacedTile(createChild);

                bool istrue = false;
                for(int i = 0; i < expandedSet.size(); i++){ //looking to see state has already been expanded
                    // cout << "Checking" << endl;
                    //cout << "checking if state has been visited" << endl;
                    if(expandedSet[i]->getState() == createChild->getState()){ //if state is visited
                         istrue = true;
                    }
                }

                bool checktrack = false;
                for(int i = 0; i < track.size(); i++){ //looking to see state has already been visited
                    // cout << "Checking" << endl;
                    //cout << "checking if state has been visited" << endl;
                    if(track[i]== createChild){ //if state is visited
                         checktrack = true;
                    }
                }

                //cout << "done checking" << endl;
                if(!istrue) { //not an old expanded state, check if its in queue
                    if(!uniform_queue.find(createChild)){ //if its not in the queue nor has it been expanded nor is it in track, basically a whole new state
                        uniform_queue.push(createChild); //add to queue
                        track.push_back(createChild); //add to track as well
                        //cout << "option" << endl;
                        //createChild->PrintState();
                    } else {
                        for(int i = 0; i < track.size(); i++) {
                            if(track[i]->getState() == createChild->getState()){ //find the one in the queue by looking through track
                                if(track[i]->getCost() + track[i]->getHCost() < createChild->getCost() + createChild->getHCost()){ //check if node in track has less cost
                                    uniform_queue.push(track[i]); //if so add it instead of new child
                                    //delete createChild;
                                    //cout << "Option" << endl;
                                    //track[i]->PrintState();
                                } else {
                                    uniform_queue.remove(createChild);
                                    uniform_queue.push(createChild); //add new lower node
                                    track[i]->setCost(createChild->getCost()); //set the tracked nodes cost to lower of the two.
                                    track[i]->setHCost(createChild->getHCost()); //have to set h cost as well for these.
                                    //cout << "Option" << endl;
                                    //createChild->PrintState(); 
                                }
                            }
                        } 
                    }
                }                 
            }
        }
    }
    return nullptr;
}

Node * Astar_ManhattanDistance(problem * prb, vector<int> start_point){
    unsigned long long numberofNodes = 0;
    unsigned long long depth = 0;
    unsigned long long nodesExpanded = 0;
    custom_priority_queue<Node*, vector<Node*>, compareNodes> uniform_queue;
    Node* begin = new Node(start_point, start_point.size());
    prb->ManhattanDistance(begin);
    long long qSize = 0;
    vector<Node*> track(0); //keep track of all states
    vector<Node*> expandedSet(0); //keep track of all states that have already been expanded.
    uniform_queue.push(begin);
    // cout << begin->getHCost() << endl;
    // string n;
    // cin >> n;
   
    while(!uniform_queue.empty()){
        if(uniform_queue.size() > qSize) {
            qSize = uniform_queue.size(); // keep track of queue size for output
        }

        Node * check = uniform_queue.top(); //taking the first node, at the beginning it will be the node passed in or default node
        
        if(track.empty()){
            track.push_back(check); // keep track of all different visited states so if we run into the same state we can compare costs.
        }
        //cout << expandedSet.size();
        // string in;
        // cin >> in;
        cout << "The best state to expand with g(n) = " << check->getCost() << " and h(n) = " << check->getHCost() << " is...." << endl;
        check->PrintState();

        uniform_queue.pop(); //remove node we are checking because we wont have to check it again since we're creating all of its children.
        if (check->getState() == prb->getGoal()){ //checking if we're at the goal state
            cout << "Goal state!" << endl << "Solution depth was: " << check->getCost() << endl;
            cout << "Number of nodes expanded: " << nodesExpanded << endl;
            cout << "Max queue size: " << qSize << endl;
            return check;
        }
        //not in goal state, check to expand nodes.
        depth++; // keep track of depth
        nodesExpanded++;
        expandedSet.push_back(check);

        for(int i = 0; i < 4; i++){ //have to check 4 operators
            if(prb->canDo(check, i)){ //if it is a valid move
                numberofNodes++; //keep track of number of nodes created
                Node* createChild = prb->Child(check, i); //create the child node
                prb->ManhattanDistance(createChild);
                //cout << createChild->getHCost() << endl;

                bool istrue = false;
                for(int i = 0; i < expandedSet.size(); i++){ //looking to see state has already been expanded
                    // cout << "Checking" << endl;
                    //cout << "checking if state has been visited" << endl;
                    if(expandedSet[i]->getState() == createChild->getState()){ //if state is visited
                         istrue = true;
                    }
                }

                bool checktrack = false;
                for(int i = 0; i < track.size(); i++){ //looking to see state has already been visited
                    // cout << "Checking" << endl;
                    //cout << "checking if state has been visited" << endl;
                    if(track[i]== createChild){ //if state is visited
                         checktrack = true;
                    }
                }

                //cout << "done checking" << endl;
                if(!istrue) { //not an old expanded state, check if its in queue
                    if(!uniform_queue.find(createChild)){ //if its not in the queue nor has it been expanded nor is it in track, basically a whole new state
                        uniform_queue.push(createChild); //add to queue
                        track.push_back(createChild); //add to track as well
                        //cout << "option" << endl;
                        //createChild->PrintState();
                    } else {
                        for(int i = 0; i < track.size(); i++) {
                            if(track[i]->getState() == createChild->getState()){ //find the one in the queue by looking through track
                                if(track[i]->getCost() + track[i]->getHCost() < createChild->getCost() + createChild->getHCost()){ //check if node in track has less cost
                                    uniform_queue.push(track[i]); //if so add it instead of new child
                                    //delete createChild;
                                    //cout << "Option" << endl;
                                    //track[i]->PrintState();
                                } else {
                                    uniform_queue.remove(createChild);
                                    uniform_queue.push(createChild); //add new lower node
                                    track[i]->setCost(createChild->getCost()); //set the tracked nodes cost to lower of the two.
                                    track[i]->setHCost(createChild->getHCost());
                                    //cout << "Option" << endl;
                                    //createChild->PrintState(); 
                                }
                            }
                        } 
                    }
                }                 
            }
        }
    }
    return nullptr;
}