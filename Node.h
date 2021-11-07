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
        Node(vector<int> st, int size){
            this->puzzle_size = size;
            this->cost = 0;
            this->Hcost = 0;
            this->state = st;
            this->parent = nullptr;
        }

        Node(int cst, vector<int> st, Node* par, int size){
            this->puzzle_size = size;
            this->cost = par->cost + 1;
            this->Hcost = 0; //for uniform it will always be 0, the other ones will have calculators to calculate this.
            this->state = st;
            this->parent = par;
        }

        ~Node(){};

        int getSize(){
            return puzzle_size;
        }

        void setCost(int i){
            this->cost = i;
        }

        void setHCost(int i) {
            this->Hcost = i;
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
            //scale for multiple puzzle sizes:
            int i = sqrt(puzzle_size);
            for(int j = 0; j < puzzle_size; j++){
                cout << state[j] << " ";
                if(((j+1) % i) == 0) {
                    cout << endl;
                } 
            }
            // for(int i = 0; i < puzzle_size; i++){
            //     cout << state[i] << " ";
            //     if(i == (sqrt(puzzle_size) - 1) || i == (2*sqrt(puzzle_size) - 1) || i == (3*sqrt(puzzle_size) - 1)){
            //         cout << endl;
            //     }
            // }
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
        //have to calculate cost of G and cost of H for uniform make sure to set H to 0.
        return l->getCost() + l->getHCost() > r->getHCost() + r->getCost();
    }
};	


#endif