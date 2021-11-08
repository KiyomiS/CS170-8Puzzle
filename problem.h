#ifndef PROBLEM_H
#define PROBLEM_H
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "Node.h"
using namespace std;

class problem {
    private:
       vector<int>problem_state; // array of size 9 to hold the problem.
       vector<int>end_goal;//goal state
    public:
        problem() {};

        problem(vector<int> input_puzzle){
            this->problem_state = input_puzzle;
            vector<int> end(0);
            for(int i = 0; i < input_puzzle.size() - 1; i ++){ // 0 1 2 3 4 5 6 7 -> 1 2 3 4 5 6 7 8 0
                end.push_back(i + 1);
            }
            end.push_back(0);
            end_goal = end;
        };

        vector<int> getGoal(){
            return end_goal;
        }

        vector<int> getState(){
            return problem_state;
        }

        vector<int> MoveLeft(vector<int> current){
            int zero_spot;
            for(int i = 0; i < current.size(); i++){
                if(current[i] == 0){
                    zero_spot = i;
                }
            }
            swap(current[zero_spot],current[zero_spot - 1]);

            return current;
        }

        vector<int> MoveRight(vector<int> current){
            int zero_spot;
            for(int i = 0; i < current.size(); i++){
                if(current[i] == 0){
                    zero_spot = i;
                }
            }
            swap(current[zero_spot],current[zero_spot + 1]);

            return current;
        }

        vector<int> MoveUp(vector<int> current) {
            int zero_spot;
            for(int i = 0; i < current.size(); i++){
                if(current[i] == 0){
                    zero_spot = i;
                }
            }
            swap(current[zero_spot],current[zero_spot - sqrt(current.size())]);

            return current;
        }

        vector<int> MoveDown(vector<int> current) {
            int zero_spot;
            vector<int> newState;
            for(int i = 0; i < current.size(); i++){
                if(current[i] == 0){
                    zero_spot = i;
                }
            }
            newState = current;
            swap(newState[zero_spot],newState[zero_spot + sqrt(current.size())]);

            return newState;
        }


        Node * Child(Node* parent, int oper){
            Node * new_child;
            if(oper == 0) {
                new_child = new Node(parent->getCost(), MoveLeft(parent->getState()), parent, parent->getSize());
                //cout << "left made" << endl;
            } else if (oper == 1) {
                new_child = new Node(parent->getCost(), MoveRight(parent->getState()), parent, parent->getSize());
                //cout << "right made" << endl;
            } else if (oper == 2) {
                new_child = new Node(parent->getCost(), MoveUp(parent->getState()), parent, parent->getSize());
                //cout << "up made" << endl;
            } else {
                new_child = new Node(parent->getCost(), MoveDown(parent->getState()), parent, parent->getSize());
                //cout << "down made" << endl;
            }
            return new_child;
        }

        bool canDo(Node * curr, int option){
            int zero_spot;
            for(int i = 0; i < 9; i++){
                if(curr->getState()[i] == 0){
                    zero_spot = i;
                }
            }
            //edge cases
            if(option == 0){
                if(zero_spot == 0 || zero_spot == 3 || zero_spot == 6){
                    return false;
                }
                return true;
            }
            if(option == 1){
                if(zero_spot == 2 || zero_spot == 5 || zero_spot == 8){
                    return false;
                }
                return true;
            }
            if(option == 2){
                if(zero_spot == 0 || zero_spot == 1 || zero_spot == 2){
                    return false;
                }
                return true;
            }
            if(option == 3){
                if(zero_spot == 6 || zero_spot == 7 || zero_spot == 8){
                    return false;
                }
                return true;
            }
            return false;
        }


        void misplacedTile(Node * node) {
            int cost = 0;
            int size = node->getSize();
            vector<int> state = node->getState();
            //calculate every number thats not in the right spot

            for(int i = 0; i < size; i++) {
                if(state[i] != 0){
                    if(state[i] != end_goal[i]){
                        cost++;
                    }
                }
            }

            node->setHCost(cost);
        }

        void ManhattanDistance(Node * node) {
            //blank's distance from final spot.
            int cost = 0;
            int size = node->getSize();
            int calc = 0;

            vector<int> state = node->getState();
            for(int i = 0; i < size; i++){
                if(state[i] != 0){
                    if(state[i] != end_goal[i]){ //if it is not in the correct spot
                        calc = i - (state[i] - 1); //calculate how off it is
                        while(calc >= sqrt(size)){ //check if it needs to move down
                            calc -= 3;
                            cost++;
                        }
                        while(calc <= -sqrt(size)){ //check if it needs to move up
                            calc +=3;
                            cost++;
                        }
                        //cout << "adding to cost" << endl;
                        cost += fabs(calc); //add left to right cost (abs takes care of left and right. easy since cost of each move is 1)
                    }
                }
            }
            node->setHCost(cost);
            //cout << node->getHCost();
        }
};


// 1 2 3   1 2 3
// 4 5 6   4 8 6
// 7 8 0   7 5 0

// 1 2 3 4 5 6 7 8 0
// 1 2 3 4 8 6 7 5 0

// 0 1 2 3 4 5 6 7 8
// 3 4 5
// 6 7 8
// up = - 3 indices, down = + 3, left = + 1, right = - 1 
//include edge cases for each.
//to scale:
//to go left it has to be less than or equal to row * sqrt(size) - 1
#endif