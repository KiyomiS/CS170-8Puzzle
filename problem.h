#ifndef PROBLEM_H
#define PROBLEM_H
#include <iostream>
#include <vector>
#include <algorithm>

#include "Node.h"
using namespace std;

class problem {
    private:
       vector<int>problem_state; // array of size 9 to hold the problem.
       vector<int>end_goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};//goal state
    public:
        problem() {};

        problem(vector<int> input_puzzle){
            this->problem_state = input_puzzle;
        };

        vector<int> getGoal(){
            return end_goal;
        }

        vector<int> getState(){
            return problem_state;
        }

        vector<int> MoveLeft(vector<int> current){
            int zero_spot;
            for(int i = 0; i < 9; i++){
                if(current[i] == 0){
                    zero_spot = i;
                }
            }
            swap(current[zero_spot],current[zero_spot - 1]);

            return current;
        }

        vector<int> MoveRight(vector<int> current){
            int zero_spot;
            for(int i = 0; i < 9; i++){
                if(current[i] == 0){
                    zero_spot = i;
                }
            }
            swap(current[zero_spot],current[zero_spot + 1]);

            return current;
        }

        vector<int> MoveUp(vector<int> current) {
            int zero_spot;
            for(int i = 0; i < 9; i++){
                if(current[i] == 0){
                    zero_spot = i;
                }
            }
            swap(current[zero_spot],current[zero_spot - 3]);

            return current;
        }

        vector<int> MoveDown(vector<int> current) {
            int zero_spot;
            vector<int> newState;
            for(int i = 0; i < 9; i++){
                if(current[i] == 0){
                    zero_spot = i;
                }
            }
            newState = current;
            swap(newState[zero_spot],newState[zero_spot + 3]);

            return newState;
        }


        Node * Child(Node* parent, int oper){
            Node * new_child;
            if(oper == 0) {
                new_child = new Node(parent->getCost(), MoveLeft(parent->getState()), parent);
                //cout << "left made" << endl;
            } else if (oper == 1) {
                new_child = new Node(parent->getCost(), MoveRight(parent->getState()), parent);
                //cout << "right made" << endl;
            } else if (oper == 2) {
                new_child = new Node(parent->getCost(), MoveUp(parent->getState()), parent);
                //cout << "up made" << endl;
            } else {
                new_child = new Node(parent->getCost(), MoveDown(parent->getState()), parent);
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
};


// 1 2 3 
// 4 5 6
// 7 8 0
// 1 2 3 4 5 6 7 8 9
// 0 1 2 3 4 5 6 7 8
// 3 4 5
// 6 7 8
// up = - 3 indices, down = + 3, left = + 1, right = - 1 
//include edge cases for each.
#endif