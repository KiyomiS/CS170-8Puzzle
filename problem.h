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
            vector<int> state = node->getState();
            int zero_spot;

            //find zero spot
            for(int i = 0; i < state.size(); i++){
                if(state[i] == 0){
                    zero_spot = i;
                }
            }


            if(zero_spot != size - 1) {

                int i = 1;
                int left_right = 0;
                bool checked = false;
                //to tell x by x puzzle
                while(i != sqrt(size) + 1) {
                    //checking how many rows down we have to go
                    //if its less than or equal to the #'s in the row, greater than the numbers in the row before
                    if((zero_spot <= (i * sqrt(size) - 1)) && (zero_spot > (i-1) * sqrt(size) - 1)) {
                        cost++;
                        if(zero_spot <= (size - 1)) {//if its in the last row you don't want to tell it to move down more so remove the last addition of move down.
                            cost--;
                            //cout << "hello??" << endl;
                        }
                        //only have to calculate left/right once, it'll always be the same no matter what row
                        if(checked == false) {
                            left_right = (i * sqrt(size) - 1) - zero_spot;
                            //cout << "computed left right" << endl;
                            checked = true;
                        }
                        //cout << "computed up down" << endl;
                    }
                    ++i;
                }
                cost = cost + left_right;
                node->setHCost(cost);
            }
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