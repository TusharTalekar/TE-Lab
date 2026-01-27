#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;    

class Node{
    vector<vector<int>> grid;
    public:
        Node(){
            for(int i=0;i<3;i++){
                vector<int> row(3,0);
                grid.push_back(row);
            }
        }
        Node(const vector<vector<int>>& g):grid(g){}
        friend class Puzzle;
    public:
        bool operator==(const Node& other) const {
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    if(this->grid[i][j] != other.grid[i][j])
                        return false;
            return true;
        }
        void operator=(const Node& other){
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    this->grid[i][j] = other.grid[i][j];
        }
};

class Puzzle{
    Node startPuzzle;
    Node goalPuzzle;
    vector<Node> visited;
    public:
        Puzzle(const vector<vector<int>>& startGrid, const vector<vector<int>>& goalGrid){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    goalPuzzle.grid[i][j] = goalGrid[i][j];
                    startPuzzle.grid[i][j] = startGrid[i][j];
                }
            }
        }
        Puzzle(const vector<vector<int>>& startGrid){
            int n=1;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    goalPuzzle.grid[i][j] = n++;
                    startPuzzle.grid[i][j] = startGrid[i][j];
                }
            }
            goalPuzzle.grid[2][2] = 0; 
        }
        Puzzle(){
            int n=1;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    goalPuzzle.grid[i][j] = n++;
                }
            }
            goalPuzzle.grid[2][2] = 0;
            inputPuzzle();
            displayPuzzle();
        }
        
        void inputPuzzle(){
            cout << "Enter the 3x3 grid for the puzzle (use 0 for empty space):" << endl;
            Node showGrid;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    // display grid with _ for empty space
                    for(int i1=0;i1<3;i1++){
                        for(int j1=0;j1<3;j1++){
                            if(i1==i && j1==j)
                                cout << "_ ";
                            else
                                cout << showGrid.grid[i1][j1] << " ";
                        }
                        cout << endl;
                    }
                    cout << "Enter value for position (" << i << "," << j << ")(use 0 for empty space): ";
                    cin >> startPuzzle.grid[i][j];
                    showGrid.grid[i][j] = startPuzzle.grid[i][j];
                }
            }
        }

        void displayPuzzle(const Node& puzzle){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    cout << puzzle.grid[i][j] << " ";
                }
                cout << endl;
            }
        }
        void displayPuzzle(){
            displayStartPuzzle();            
            displayGoalPuzzle();
        }
        void displayStartPuzzle(){
            cout << "Start Puzzle:" << endl;
            displayPuzzle(startPuzzle);
        }
        void displayGoalPuzzle(){
            cout << "Goal Puzzle:" << endl;
            displayPuzzle(goalPuzzle);
        }

        void solve(){
            if(!isSolvable()){
                cout << "This puzzle is not solvable." << endl;
                return;
            }
            cout << "Solving." << endl;
            int iteration = 0;
            bool flag=true;
            while(!(startPuzzle == goalPuzzle)&&flag){
                flag= makeBestMove();
            }
            if(!flag){
                cout << "Could not solve the puzzle." << endl;
                return;
            }
            cout << "Puzzle solved." << endl;
        }   

        void swapTiles(int x1, int y1, int x2, int y2){
            int temp = startPuzzle.grid[x1][y1];
            startPuzzle.grid[x1][y1] = startPuzzle.grid[x2][y2];
            startPuzzle.grid[x2][y2] = temp;
        }

        bool isGoalState(){
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    if(startPuzzle.grid[i][j] != goalPuzzle.grid[i][j])
                        return false;
            return true;
        }
        
        int calculateHeuristic(Node& puzzle){
            int misplacedTiles = 0;
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    if(puzzle.grid[i][j] != 0 && puzzle.grid[i][j] != goalPuzzle.grid[i][j])
                        misplacedTiles++;
            return misplacedTiles;
        }
        int calculateHeuristic(){
            return calculateHeuristic(startPuzzle);
        }

        bool isSolvable(){
            vector<int> flatPuzzle;
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    if(startPuzzle.grid[i][j] != 0)
                        flatPuzzle.push_back(startPuzzle.grid[i][j]);

            int inversions = 0;
            for(size_t i=0;i<flatPuzzle.size();i++){
                for(size_t j=i+1;j<flatPuzzle.size();j++){
                    if(flatPuzzle[i] > flatPuzzle[j])
                        inversions++;
                }
            }
            return (inversions % 2 == 0);
        }

        bool makeBestMove(){
            vector<Node> moves = getPossibleMoves();
            if(moves.empty()){
                cout << "No possible moves available." << endl;
                return false;
            }
            int idx=0,minH=INT_MAX;
            for(int i=0;i<moves.size();i++){
                int h=calculateHeuristic(moves[i]);
                if(h < minH){
                    minH = h;
                    idx =i;
                }   
            }
            startPuzzle = moves[idx];
            visited.push_back(startPuzzle);     
            cout << "Next Move with Heuristic " << minH << ":" << endl;
            displayPuzzle(startPuzzle);
            return true;
        }

        vector<Node> getPossibleMoves(){
            vector<Node> moves;
            int zeroX, zeroY;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(startPuzzle.grid[i][j] == 0){
                        zeroX = i;
                        zeroY = j;
                    }
                }
            }
            vector<pair<int,int>> directions = {{-1,0},{1,0},{0,-1},{0,1}};
            for(auto dir : directions){
                int newX = zeroX + dir.first;
                int newY = zeroY + dir.second;
                if(newX >= 0 && newX < 3 && newY >= 0 && newY < 3){
                    vector<vector<int>> newGrid = startPuzzle.grid;
                    swap(newGrid[zeroX][zeroY], newGrid[newX][newY]);
                    Node n=Node();
                    n.grid=newGrid;
                    if(find(visited.begin(), visited.end(), Node(newGrid)) == visited.end()){
                        moves.push_back(n);
                    }
                }
            }
            return moves;
        }
        

};

int main(){
    // Puzzle p({{1,2,3},{0,4,6},{7,5,8}}, {{1,2,3},{4,5,6},{7,8,0}});
    // Puzzle p({{1,2,3},{4,5,6},{8,7,0}}, {{1,2,3},{4,5,6},{7,8,0}});


    Puzzle p;
    string menu="1. Input Puzzle. \n2. Display Puzzle. \n3. Solve Puzzle. \n4. Exit\n";
    while (true){
        int choice;
        cout <<endl<< menu;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice){
        case 1:
            p.inputPuzzle();
            break;           
        case 2:
            p.displayPuzzle();
            break;
        case 3:
            p.solve();
            break;
        case 4:
            cout << "Thank You !" << endl;
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
            break; 
        } 
    }
    
    // p.displayPuzzle();
    // p.solve();
    // p.displayStartPuzzle();
    cout << "Hello World!" << endl;
    return 0;
}