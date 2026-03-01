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
    long long col ;
    long long diag1;
    long long diag2;
    public:
    queens(int n):n(n),
        pos(n),
        col(0),
        diag1(0),
        diag2(0)
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
        int sym=1;
        for(int i=n-1;i>=0;i--){
            int s=sym;
           sym=(sym+1)%2;
            int x=pos[i].x;
            int y=pos[i].y;
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
    bool placeQueen(int row) {
        if (row == n) return true;

        for (int c = 0; c < n; c++) {
            long long cMask = 1LL << c;
            long long d1Mask = 1LL << (row - c + n);
            long long d2Mask = 1LL << (row + c);

            if (!(col & cMask) &&
                !(diag1 & d1Mask) &&
                !(diag2 & d2Mask)) {

                pos[row] = {c, row};

                col |= cMask;
                diag1 |= d1Mask;
                diag2 |= d2Mask;

                if (placeQueen(row + 1)) return true;

                col &= ~cMask;
                diag1 &= ~d1Mask;
                diag2 &= ~d2Mask;
            }
        }
        return false;
    }
};

int main(){
    int n=32;
    queens q(n);
    auto start = high_resolution_clock::now();
    q.solveQueens(n);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Execution time: " << (float)(duration.count())/1000 << " seconds" << endl;
    cout<<"Hello"<<endl;
    return 0;
}