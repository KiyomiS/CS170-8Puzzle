#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>

using namespace std;

class Node{
    private:
        int cost;
        int Hcost;
        int puzzle_size; //to allow for bigger puzzles instead of an 8x8
        vector<int> state;
        Node *parent;
    public:
        Node(vector<int> st){
            this->cost = 0;
            this->Hcost = 0;
            this->state = st;
            this->parent = nullptr;
        }

        Node(int cst, vector<int> st, Node* par){
            this->cost = par->cost + 1;
            this->state = st;
            this->parent = par;
        }

        ~Node(){};

        void setCost(int i){
            this->cost = i;
        }

        int getHCost() const {
            return Hcost;
        }

        int getCost() const {
            return cost;
        }

        vector<int> getState() const{
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

        bool operator==(const Node & rhs) const{
            return state == rhs.getState();
        }

        bool operator>(const Node& rhs) const{
            return this->getCost() > rhs.getCost();
        }


};

struct compareNodes{ //ordering from lowest to greatest
    bool operator()(const Node *l, const Node * r) const {
        return l->getCost() > r->getCost();
    }
};	


#endif