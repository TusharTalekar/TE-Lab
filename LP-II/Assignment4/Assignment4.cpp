#include<iostream>
#include<vector>
using namespace std;


class queens{
    vector<int> pos;
    int n;
    vector<bool> col;
    vector<bool> diag1; // r - c + n
    vector<bool> diag2; // r + c
    public:
    queens(int n):n(n),
        pos(n),
        col(n, false),
        diag1(2*n, false),
        diag2(2*n, false)
    {}

    void clearCache(){
        col.clear();
        diag1.clear();
        diag2.clear();
    }
    
    void updateN(int n){
        this->n=n;
        clearCache();
        col.resize(n,false);
        diag1.resize(2*n,false);
        diag2.resize(2*n,false);
    }

    void solveQueens(){
        if(!placeQueen(0)){
            cout<<"No solution"<<endl;
            return;
        }
        displayCoord();
        updateN(this->n);
    }
    
    void displayCoord(){
        for(int i=0;i<n;i++){
            cout<<"X: "<<pos[i]<<"  Y: "<<i<<endl;
        }
    }
    
    void displayBoard(){
        int sym=1;
        for(int i=n-1;i>=0;i--){
            int s=sym;
            sym=(sym+1)%2;
            int x=pos[i];
            int y=i;
            for(int j=0;j<n;j++){
                if(j==x){
                    cout<<"OOO";
                }else if(s==0){
                    cout<<"...";
                }else{
                    cout<<"___";
                }
                s=(s+1)%2;
            }
            cout<<endl;
        }
    }
    
    bool placeQueen(int row){
        if(row>=n){
            return true;
        }
        for(int c = 0; c < n; c++){
            if(!col[c] && !diag1[row - c + n] && !diag2[row + c]){
                pos[row] = c;

                col[c] = diag1[row - c + n] = diag2[row + c] = true;

                if(placeQueen(row + 1)) return true;

                col[c] = diag1[row - c + n] = diag2[row + c] = false;
            }
        }
        return false;
    }
};


int main(){
    int n=30;

    cout<<"Enter size of board: ";
    cin>>n;
    queens q(n);
    q.solveQueens();

    string menu="1. Enter size of board. \n2. Find solution. \n3. Display Board. \n4. Exit.";

    int choice;
    do{
        cout<<endl<<menu<<endl;
        cout<<"Enter choice:";
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"Enter number: ";
                cin>>n;
                q.updateN(n);
                break;
            case 2:
                q.solveQueens();
                break;
            case 3:
                q.displayBoard();
                break;
            default:
                cout<<"Invalid choice !"<<endl;
                break;
        }
    }while(choice!=4);
    
    // q.solveQueens(n);
    // q.displayBoard();

    cout<<"Hello World"<<endl;
    return 0;
}