#include "board.h"

using namespace std;
//Constructor
Board::Board(){
    blank = make_pair(2, 2); //location of blank
    depth = 0; //amount of node in the tree.
    fin = numeric_limits<int>::max();//set to the largest possible value

}
//Display board
void Board::display(){
    for(unsigned i = 0; i < 3; i++){
        for(unsigned j = 0; j < 2; j++){
            cout << init[i][j] << ' ';
        }
        cout << init[i][2] << '\n';
    }
}
//Create board
void Board::set(){
    int n, row = 3, column = 3;
    vector<int> prevs; //previous answers

    cout << "Enter your puzzle, use a zero represent the blank\n";
    for(unsigned i = 0; i < row; i++){
        cout << "Enter the numbers for row " << i + 1 << ", use spaces between the numbers:\n";
        for(unsigned j = 0; j < column; j++){
            cin >> n;
            //Error checking
            if(find(prevs.begin(), prevs.end(), n) != prevs.end()){
                cout << "No duplicates.\n";
                return; //leaves function if input was already used
            } else {
                init[i][j] = n;
                if(n == 0){
                    blank = make_pair(j, i);
                }
                prevs.push_back(n);
            }
        }
    }
}
//Initial 
void Board::setDefault(){
    init[0][0] = 1; init[0][1] = 2; init[0][2] = 3;
    init[1][0] = 4; init[1][1] = 0; init[1][2] = 6;
    init[2][0] = 7; init[2][1] = 5; init[2][2] = 8;

    blank = make_pair(1, 1);
}

void Board::setGoal(){
    init[0][0] = 1; init[0][1] = 2; init[0][2] = 3;
    init[1][0] = 4; init[1][1] = 5; init[1][2] = 6;
    init[2][0] = 7; init[2][1] = 8; init[2][2] = 0;
}

bool Board::isGoal(Board b){
    if((init[0][0] == b.init[0][0]) && (init[0][1] == b.init[0][1]) && 
    (init[0][2] == b.init[0][2]) && (init[1][0] == b.init[1][0]) &&
    (init[1][1] == b.init[1][1]) && (init[1][2] == b.init[1][2]) &&
    (init[2][0] == b.init[2][0]) && (init[2][1] == b.init[2][1]) &&
    (init[2][2] == b.init[2][2])){
        return true;
    }
    return false;
}
//Get's amount of misplacements currently on Board
int Board::misplacements(){ 
    return ((init[0][0] != 1) + (init[0][1] != 2) + (init[0][2] != 3) //trues return 1
        + (init[1][0] != 4) + (init[1][1] != 5) + (init[1][2] != 6)
        + (init[2][0] != 7) + (init[2][1] != 8));
}
//Calculate Manhattan Distance
int Board::manhatDist(){
    int dist = 0, x, y, v; //distance, goal row, goal column, cell value

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 0; j++){
            if((v = init[i][j]) != 0){      // 0 1 2    1 2 3
                x = (v - 1) / 3;            // 3 4 5 == 4 5 6
                y = (v - 1) % 3;            // 6 7 8    7 8 9
                dist += abs(x - i) + abs(y - j);
            }
        }
    }
    return dist;
}

bool Board::moveU(){
    if((blank.first - 1) < 0){ //reaches board edge
        return false;
    } else { //swaps
        int temp = init[blank.first-1][blank.second];
        init[blank.first][blank.second] = temp;
        init[blank.first-1][blank.second] = 0;
        blank = make_pair(blank.first - 1, blank.second);
        return true;
    }
}

bool Board::moveD(){
    if((blank.first + 1) > 2){ //reaches board edge
        return false;
    } else { //swaps
        int temp = init[blank.first+1][blank.second];
        init[blank.first][blank.second] = temp;
        init[blank.first+1][blank.second] = 0;
        blank = make_pair(blank.first + 1, blank.second);
        return true;
    }
}

bool Board::moveL(){
    if((blank.second - 1) < 0){ //reaches board edge
        return false;
    } else { //swaps
        int temp = init[blank.first][blank.second-1];
        init[blank.first][blank.second] = temp;
        init[blank.first][blank.second-1] = 0;
        blank = make_pair(blank.first, blank.second - 1);
        return true;
    }
}

bool Board::moveR(){
    if((blank.second + 1) > 2){ //reaches board edge
        return false;
    } else { //swaps
        int temp = init[blank.first][blank.second+1];
        init[blank.first][blank.second] = temp;
        init[blank.first][blank.second+1] = 0;
        blank = make_pair(blank.first, blank.second + 1);
        return true;
    }
}

int Board::getF(){
    return fin;
}

void Board::calcF(){
    if(heur == 1){ //Uniform A*
        fin = depth;
        hm.push_back(0);
    } else if(heur == 2){ //Misplacement A*
        fin = misplacements() + depth;
        hm.push_back(misplacements());
    } else { //Manhattan Distance A*
        fin = manhatDist() + depth;
        hm.push_back(manhatDist());
    }
}
//Outputs the path that the function chose showing the g(n) and h(n) value for each step
void Board::expand(Board b, Board goal){
    //for 
    for(int i = 0; i < goal.m.size(); i++){
        if(goal.m[i] == 1){ //When it went up
            b.moveU();
            cout << "The best state to expand with g(n) = " << goal.gm[i] << " and h(n) = "
                << goal.hm[i] << " is:\n";
            b.display();
            cout << "Expanding...\n";
        } if(goal.m[i] == 2){ //When it went down
            b.moveD();
            cout << "The best state to expand with g(n) = " << goal.gm[i] << " and h(n) = "
                << goal.hm[i] << " is:\n";
            b.display();
            cout << "Expanding...\n";
        } if(goal.m[i] == 3){ //When it went left
            b.moveL();
            cout << "The best state to expand with g(n) = " << goal.gm[i] << " and h(n) = "
                << goal.hm[i] << " is:\n";
            b.display();
            cout << "Expanding...\n";
        } if(goal.m[i] == 4){ //When it went right
            b.moveR();
            cout << "The best state to expand with g(n) = " << goal.gm[i] << " and h(n) = "
                << goal.hm[i] << " is:\n";
            b.display();
            cout << "Expanding...\n";
        }
        cout << '\n';
    }
}

//helper function/class
class lowF{ //used to sort the queue based on the lowest f value
    public:
        bool operator()(Board a, Board b){
            return a.getF() > b.getF(); //set priority based on the lowest f
        }
};

Board Board::aStar(Board initial, int expansion, int n){
    priority_queue<Board, vector<Board>, lowF> q;
    vector<Board> nodes;
    Board current, goal;
    goal.setGoal();
    q.push(initial);
//top of the queue, the board of the movement with the lowest f value goes through each movement to add to queue
//Will do this until it reach end goal
    do {
        current = q.top();
        q.pop();
        current.depth++;
        current.m.push_back(current.direction); //stores move
        current.gm.push_back(current.depth); //stores g
        current.calcF();
        nodes.push_back(current);
        current.display(); //Used to testing purpose of seeing search process
        cout << '\n';
//up
        if(current.moveU()){
            current.direction = 1;
            q.push(current);
            current.moveD();
            expansion++;
        }
//down
        if(current.moveD()){
            current.direction = 2;
            q.push(current);
            current.moveU();
            expansion++;
        }
//left
        if(current.moveL()){
            current.direction = 3;
            q.push(current);
            current.moveR();
            expansion++;
        }
//right
        if(current.moveR()){
            current.direction = 4;
            q.push(current);
            current.moveL();
            expansion++;
        }
        if(q.size() > n){
            n = q.size();
        }
    } while(!current.isGoal(goal));//change

    return current;
}
