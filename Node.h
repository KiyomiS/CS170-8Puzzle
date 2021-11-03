#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>

using namespace std;

class Node{
    private:
        int cost;
        vector<int> state;
        Node *parent;
    public:
        Node(){
            this->cost = 0;
            this->state = state;
            this->parent = nullptr;
        }

        Node(int cst, vector<int> st, Node* par){
            cost = par->cost + 1;
            state = st;
            parent = par;
        }

        ~Node(){};

        int getCost() {
            return cost;
        }

        vector<int> getState() {
            return state;
        }

        void PrintState(){
            for(int i = 0; i < 9; i++){
                cout << state[i] << " ";
                if(i == 2 || i == 5 || i == 8){
                    cout << endl;
                }
            }
            cout << endl;
        }
};


#endif