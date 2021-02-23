#include "board.h"

using namespace std;

int main(){
//Declarations
    Board b; //Board
    int e, n = 0; //expansions, nodes
    vector<Board> no;
    unsigned puzzle; //Determines when puzzle is default or not
    unsigned algorithm; //Determines the algorithm used
//Prompt
    cout << "Welcome to Brian Corbita 8-puzzle solver.\n";
    cout << "\"1\" to use a default puzzle, or \"2\" to enter your own puzzle.\n";

    cin >> puzzle;

    if(puzzle == 1){
        b.setDefault();
    } else if(puzzle == 2){
        b.set();
    } else{
        cout << "Invalid option\n";
        exit(0);
    }
    cout << "Choose an algorithm: \n";
    cout << "1. Uniform Cost Search\n" << "2. A* with Misplaced Tile Heuristic\n"
        << "3. A* with Manhattan Distance Heuristic\n";
    
    cin >> b.heur;
//Searches
    Board g = b.aStar(b, e, n);

    cout << "Expanding state\n";
//Output path
    b.expand(b,g);

    cout << "Goal!\n";

    cout << "To solve the problem, the algorithm expanded by " << e << " nodes.\n";
    cout << "The max number of nodes in the queue at any time was " << n << ".\n";
    cout << "The depth of the goal node is " << g.depth << '\n';
}