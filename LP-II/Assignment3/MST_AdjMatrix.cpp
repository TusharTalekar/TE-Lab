#include<iostream>
#include<climits>
#include<map>
#include<vector>
using namespace std;


class MST{
    static int minKey(vector<int> &key,vector<bool> &isInMST){
        int n=key.size();
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
        static vector<int> prims(vector<vector<int>> adjMat){
            int n=adjMat.size();
            if(n==0) return {};
            vector<int> parent(n);
            vector<int> key(n);
            vector<bool> isInMST(n);

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
            // displayMST(parent,adjMat);
            return parent;
        }

        static void displayMST(vector<int> parent,const vector<vector<int>> &adjMat){
            int n=adjMat.size();
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

};

template<typename T>
class Graph {
    vector<vector<int>> adjMat;
    map<T,int> indexNum;
    map<int,T> data;
    
    public:
        Graph(){}

        Graph(vector<vector<int>> mat,vector<T> nodes) {
            int n=nodes.size();
            adjMat=mat;
            adjMat.resize(n,vector<int>(n));
            for(int i=0;i<n;i++){
                adjMat[i].resize(n,0);
                indexNum[nodes[i]]=i;
                data[i]=nodes[i];
            }
        }

        void clearGraph() {
            adjMat.clear();
            indexNum.clear();
            data.clear();
            cout << "Graph cleared successfully! You can now create a new graph.\n";
        }

        void addNode(T node) {
            if(indexNum.find(node) != indexNum.end()){
                cout << "Node already exists!\n";
                return;
            }
            int newIndex = adjMat.size();

            for(auto &row : adjMat){
                row.push_back(0);
            }
            adjMat.push_back(vector<int>(newIndex + 1, 0));

            indexNum[node] = newIndex;
            data[newIndex] = node;

            cout << "Node added successfully!\n";
        }

        void addEdge(T u, T v, int weight){
            if(indexNum.find(u) == indexNum.end() || indexNum.find(v) == indexNum.end()){
                cout << "One or both nodes not found!\n";
                return;
            }

            int i = indexNum[u];
            int j = indexNum[v];

            adjMat[i][j] = weight;
            adjMat[j][i] = weight;

            cout << "Edge added successfully!\n";
        }

        void primsMST(){
            vector<int> parentNodes=MST::prims(adjMat);
            displayMST(parentNodes,adjMat);
        }
        
        void displayMST(vector<int> parent,const vector<vector<int>> &adjMat){
            int n=adjMat.size();
            int minCost=0;
            for(int i=0;i<n;i++){
                if(parent[i]>-1){
                    cout<<data[parent[i]]<<" -> "<<data[i]<<"\t";
                    cout<<adjMat[i][parent[i]];
                    minCost+=adjMat[i][parent[i]];
                    cout<<endl;
                }
            }
            cout<<minCost<<endl;
        }

        void display() {
            int n=adjMat.size();
            cout.width(10);
            cout<<"Nodes";
            for(int i=0;i<n;i++){
                cout.width(10);
                cout<<data[i];
            }
            cout<<endl;
            for(int i = 0; i < n; i++) {
                cout.width(10);
                cout<<data[i];
                for(int j = 0; j < n; j++) {
                    cout.width(10);
                    cout << adjMat[i][j];
                }
                cout << endl;
            }
        }

};


int main(){

    Graph<string> g;

    int choice;
    string u, v;
    int weight;
    string menu="1. Add Node. \n2. Add Edge. \n3. Display Graph. \n4. Calculate MST (Prim's). \n5. Delete entire graph. \n0. Exit.";
    do {
        cout<<endl<<menu;
        cout<<endl<<"Enter choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                cout << "Enter node name: ";
                cin >> u;
                g.addNode(u);
                break;

            case 2:
                cout << "Enter first node: ";
                cin >> u;
                cout << "Enter second node: ";
                cin >> v;
                cout << "Enter weight: ";
                cin >> weight;
                g.addEdge(u, v, weight);
                break;
            case 3:
                g.display();
                break;
            case 4:
                g.primsMST();
                break;
            case 5:
                g.clearGraph();
            case 0:
                cout << "Thank You !"<<endl;
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 0);
    
    
    // 1 A 1 B 1 C 2 A B 5 2 B C 3 4


    // Graph<string> g({
    //     {0, 2, 3, 0, 0},
    //     {2, 0, 0, 15, 2},
    //     {3, 0, 0, 7, 1},
    //     {0, 15, 7, 0, 0},
    //     {0, 2, 1, 0, 0}
    // },
    // {"A","B","C","D","E"});
    // g.display();
    // g.primsMST();




    // vector<int> mstParent=MST::prims({
    //     {0, 2, 3, 0, 0},
    //     {2, 0, 0, 15, 2},
    //     {3, 0, 0, 7, 1},
    //     {0, 15, 7, 0, 0},
    //     {0, 2, 1, 0, 0}
    // });


    return 0;
}