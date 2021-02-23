#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

class Board{

private:
    int init[3][3]; //[row][column]
    int fin; //h(n) + g(n) determining factor for A*
    vector<int> m, hm, gm; //move history, estimated move history, movement cost history

public:
    int depth, heur, prev; //current depth, heuristic type, previous move
    pair<int, int> blank; //blank location
    int direction = 0; //previous direction 0 since it hasn't gone a direction yet

    Board();
//Output
    void display();
//Input
    void set();
//Set default initial board based on the one shown on the project documentation
    void setDefault();
//Set board intended to meet
    void setGoal(); //Need?
//Checks if board 
    bool isGoal(Board board);

    int misplacements();
    int manhatDist();
//Movement
    bool moveU(); //up
    bool moveD(); //down
    bool moveL(); //left
    bool moveR(); //right
//Getter
    int getF();
 //Calculates the fin value
    void calcF();
//Expands the tree via testing directions
    void expand(Board b, Board goal);
//A* algorithm
    Board aStar(Board b, int expansions, int n);

};