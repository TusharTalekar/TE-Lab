#include<iostream>
#include<climits>
using namespace std;

const int n=10;

class MST{
    static int minKey(int key[],bool isInMST[]){
        int minIdx,minVal=INT_MAX;
        for(int i=0;i<n;i++){
            if(!isInMST[i] && key[i]<minVal){
                minVal=key[i];
                minIdx=i;
            }
        }
        return minIdx;
    }
    public:
        static void prims(int adjMat[][n]){
            int parent[n];
            int key[n];
            bool isInMST[n];

            for(int i=0;i<n;i++){
                key[i]=INT_MAX;
                isInMST[i]=false;
                parent[i]=-1;
            }
            
            key[0]=0;

            for(int cnt=0;cnt<n-1;cnt++){
                int i=minKey(key,isInMST);

                isInMST[i]=true;

                for(int j=0;j<n;j++){
                    if(adjMat[i][j] && !isInMST[j] && adjMat[i][j]<key[j]){
                        key[j]=adjMat[i][j];
                        parent[j]=i;
                    }
                }
            }
            displayMST(isInMST,parent,adjMat);
        }

        static void displayMST(bool isInMST[],int parent[],const int adjMat[][n]){
            int minCost=0;
            for(int i=0;i<n;i++){
                if(parent[i]>-1){
                    cout<<parent[i]<<" -> "<<i<<"\t";
                    cout<<adjMat[i][parent[i]];
                    minCost+=adjMat[i][parent[i]];
                    cout<<endl;
                }
            }
            cout<<minCost<<endl;
        }

        static void displayMatrix(int adjMat[][n]) {
            cout << "Adjacency Matrix:\n";
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    cout << adjMat[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }

    };

int main(){
    int matrix[n][n]={
        {0, 2, 3, 0, 0},
        {2, 0, 0, 15, 2},
        {3, 0, 0, 7, 1},
        {0, 15, 7, 0, 0},
        {0, 2, 1, 0, 0}
    };
MST::displayMatrix(matrix);
    MST::prims(matrix);


    return 0;
}