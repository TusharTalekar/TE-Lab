#include <chrono>
#include<iostream>
#include<vector>
#include<ctime>
using namespace std;
using namespace std::chrono;

struct positions{
    int x,y;
    positions(int X=0,int Y=0):x(X),y(Y){}

};
class queens{
    vector<positions> pos;
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
    
    void solveQueens(int n){
        if(!placeQueen(0)){
            cout<<"No solution"<<endl;
            return;
        }
        displayCoord();
    }
    void displayCoord(){
        for(int i=0;i<n;i++){
            cout<<"X: "<<pos[i].x<<"  Y: "<<pos[i].y<<endl;
        }
        // int sym=1;
        // for(int i=n-1;i>=0;i--){
        //     int s=sym;
        //     sym=(sym+1)%2;
        //     int x=pos[i].x;
        //     int y=pos[i].y;
        //     for(int j=0;j<n;j++){
        //         if(j==x){
        //             cout<<"OOO";
        //         }else if(s==0){
        //             cout<<"...";
        //         }else{
        //             cout<<"___";
        //         }
        //         s=(s+1)%2;
        //     }
        //     cout<<endl;
        // }
    }
    bool placeQueen(int row){
        if(row>=n){
            return true;
        }
        // pos[row].y=row;
        // for(int i=0;i<n;i++){
        //     pos[row].x=i;
        //     if(isSafe(row)){
        //         // cout<<pos[row].x<<" "<<pos[row].y<<endl;
        //         if(placeQueen(row+1)){
        //             return true;
        //         }
        //     }
        // }
        for(int c = 0; c < n; c++){
            if(!col[c] && !diag1[row - c + n] && !diag2[row + c]){
                pos[row] = {c, row};

                col[c] = diag1[row - c + n] = diag2[row + c] = true;

                if(placeQueen(row + 1)) return true;

                col[c] = diag1[row - c + n] = diag2[row + c] = false;
            }
        }
        return false;
    }
    // bool isSafe(int row){
    //     int x=pos[row].x;
    //     int y=pos[row].y;
    //     for(int i=0;i<row;i++){
    //         int x1=pos[i].x;
    //         int y1=pos[i].y;
    //         if(x1==x || y1==y || abs(y1-y)==abs(x1-x)){
    //             return false;
    //         }
    //     }
    //     return true;
    // }
};

int main(){
    int n=29;
    queens q(n);
    auto start = high_resolution_clock::now();
    q.solveQueens(n);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Execution time: " << (float)(duration.count())/1000 << " seconds" << endl;
    cout<<"Hello"<<endl;
    return 0;
}