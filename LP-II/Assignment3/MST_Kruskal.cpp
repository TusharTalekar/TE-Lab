// Kruskal’s
// 1. Sorts all edges by increasing weight
// 2. Adds edges one by one to the MST
// 3. Skips any edge that forms a cycle
// 4. Stops when V − 1 edges are selected

// 1. Create a separate set for each vertex (MakeSet).
// 2. Sort all edges in non-decreasing order of weight.
// 3. For each edge (u, v):
//     If u and v are in different sets:
//     Add edge to MST
//     Union the sets
//     Else:
//     Ignore the edge (it forms a cycle)
// 4. Stop when MST has V − 1 edges.


#include<iostream>
#include<algorithm>
using namespace std;

const int n = 5;
const int MAX = 25;

struct Edge {
    int u, v, w;
};

class MST {

    static int find(int parent[], int i) {
        while(parent[i] != i)
            i = parent[i];
        return i;
    }

    static void unite(int parent[], int u, int v) {
        int u_set = find(parent, u);
        int v_set = find(parent, v);
        parent[u_set] = v_set;
    }

public:
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

    static void kruskal(int adjMat[][n]) {
        Edge edges[MAX];
        int edgeCount = 0;

        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                if(adjMat[i][j] != 0) {
                    edges[edgeCount].u = i;
                    edges[edgeCount].v = j;
                    edges[edgeCount].w = adjMat[i][j];
                    edgeCount++;
                }
            }
        }
        
        sort(edges, edges + edgeCount, [](Edge a, Edge b) {
            return a.w < b.w;
        });

        int parent[n];
        for(int i = 0; i < n; i++)
            parent[i] = i;

        Edge mst[n-1];
        int count = 0;
        for(int i = 0; i < edgeCount && count < n - 1; i++) {

            int u = edges[i].u;
            int v = edges[i].v;

            if(find(parent, u) != find(parent, v)) {
                mst[count++] = edges[i];   
                unite(parent, u, v);
            }
        }

        displayMST(mst, count);
        }

    static void displayMST(Edge mst[], int count) {
        int minCost = 0;

        cout << "Edges in MST:\n";
        for(int i = 0; i < count; i++) {
            cout << mst[i].u << " - " << mst[i].v
                << "   " << mst[i].w << endl;
            minCost += mst[i].w;
        }

        cout << "Minimum Cost: " << minCost << endl;
    }

};

int main() {

    int matrix[n][n] = {
        {0, 2, 3, 0, 0},
        {2, 0, 0, 15, 2},
        {3, 0, 0, 7, 1},
        {0, 15, 7, 0, 0},
        {0, 2, 1, 0, 0}
    };

    // MST::displayMatrix(matrix);
    MST::kruskal(matrix);


    return 0;
}
