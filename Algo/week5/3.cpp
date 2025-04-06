
#include <iostream>
#include <vector>
#include <iomanip>
#include <functional>
#include <sstream>
#include <string>
#include <utility> // For std::pair
#include <algorithm> // For std::min

using namespace std;

const int INF = 999;

typedef vector<vector<int>> matrix;

void floid(int n , matrix & D,matrix &P){
    
    for (int k=1; k<=n;k++){
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (D[i][j] > D[i][k] + D[k][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k; // Store the intermediate vertex
                }
            }
            
        }
        
    }


}

vector<int> get_path(int u, int v, const matrix &D, const matrix &P) {
    if (D[u][v] == INF) return {}; // No path exists
    
    if (u == v) return {u}; // Self-loop
    
    vector<int> path;
    
    function<void(int, int)> reconstruct = [&](int start, int end) {
        int k = P[start][end]; 
        
        if (k == -1) { // Direct edge or no path
            path.push_back(start); // Add source vertex (1-indexed)
            if (start != end) // Don't add destination twice if same as source
                path.push_back(end); // Add destination vertex (1-indexed)
        } else {
            // Recursively reconstruct path through intermediate vertex k
            reconstruct(start, k);
            path.pop_back(); // Remove duplicate vertex
            reconstruct(k, end);
        }
    };
    
    reconstruct(u, v);
    return path;
}


int main(){

    int n , m;
    cin >> n >> m;
    matrix D(n+1, vector<int>(n+1, INF));
    matrix P(n+1, vector<int>(n+1, 0)); 

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        D[u][v] = w;
        P[u][v] = 0; 
    }
    
    int k;
    cin >> k;

    vector<pair<int, int>> queries(k);
    for (int i = 0; i < k; ++i) {
        int s, e;
        cin >> s >> e;
        queries[i] = {s, e};
    }

    floid(n, D , P);

    for (int i = 1; i <= n; i++) {

        cout << D[i][0] ;
        for(int j = 2; j <= n; j++) {
            cout << " " << D[i][j];
        }
        cout << endl;
    }


    for ( int i = 1; i <= n; i++)
    {
        cout << P[i][0] ;
        for(int j = 2; j <= n; j++)
        {
            cout << " " << P[i][j];
        }
        cout << endl;
    }

    for (auto [u, v] : queries) {
        vector<int> path = get_path(u, v, D, P);
        
        if (path.empty()) {
            cout << "NONE\n";
        } else {
            for (int i = 0; i < path.size(); ++i)
                cout << path[i] << (i == path.size() - 1 ? "\n" : " ");
        }
    }
    
    
    


}

