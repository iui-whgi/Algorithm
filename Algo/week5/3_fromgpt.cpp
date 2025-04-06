#include <iostream>
#include <vector>
#include <iomanip>
#include <functional>
#include <sstream>
#include <string>

using namespace std;

const int INF = 999;

int N, M, K;
vector<vector<int>> D;
vector<vector<int>> P;

void floyd_warshall() {
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k + 1; // Store 1-indexed intermediate vertex
                }
            }
        }
    }
}

// Simpler path reconstruction function
vector<int> get_path(int u, int v) {
    if (D[u][v] == INF) return {}; // No path exists
    
    if (u == v) return {u + 1}; // Self-loop
    
    vector<int> path;
    
    // Helper function to reconstruct the path from u to v
    function<void(int, int)> reconstruct = [&](int start, int end) {
        int k = P[start][end] - 1; // Convert to 0-indexed
        
        if (k < 0) { // Direct edge or no path
            path.push_back(start + 1); // Add source vertex (1-indexed)
            if (start != end) // Don't add destination twice if same as source
                path.push_back(end + 1); // Add destination vertex (1-indexed)
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

// Function to process input from a string instead of cin
void process_from_string(const string& input) {
    stringstream ss(input);
    
    ss >> N >> M;
    D.assign(N, vector<int>(N, INF));
    P.assign(N, vector<int>(N, 0));
    
    for (int i = 0; i < N; ++i) D[i][i] = 0;
    
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        ss >> u >> v >> w;
        D[u - 1][v - 1] = w;
        P[u - 1][v - 1] = 0; // No intermediate vertex for direct edges
    }
    
    ss >> K;
    vector<pair<int, int>> queries(K);
    for (int i = 0; i < K; ++i) {
        int s, e;
        ss >> s >> e;
        queries[i] = {s - 1, e - 1};
    }
    
    floyd_warshall();
    
    // Output: D table
    cout << "D matrix:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << D[i][j] << (j == N - 1 ? "\n" : " ");
    }
    
    // Output: P table
    cout << "\nP matrix:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << P[i][j] << (j == N - 1 ? "\n" : " ");
    }
    
    // Output: Actual paths
    cout << "\nPaths for queries:" << endl;
    for (auto [u, v] : queries) {
        vector<int> path = get_path(u, v);
        cout << "Path from " << u+1 << " to " << v+1 << ": ";
        if (path.empty()) {
            cout << "NONE\n";
        } else {
            for (int i = 0; i < path.size(); ++i)
                cout << path[i] << (i == path.size() - 1 ? "\n" : " ");
        }
    }
}

int main() {
    // Sample input from the problem description
    string sample_input = R"(5 10
1 2 1
1 4 1
1 5 5
2 1 9
2 3 3
2 4 2
3 4 4
4 3 2
4 5 3
5 1 3
25
1 1
1 2
1 3
1 4
1 5
2 1
2 2
2 3
2 4
2 5
3 1
3 2
3 3
3 4
3 5
4 1
4 2
4 3
4 4
4 5
5 1
5 2
5 3
5 4
5 5)";

    process_from_string(sample_input);
    
    return 0;
}