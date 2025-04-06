#include <iostream>
#include <vector>
#include <iomanip>
#include <functional>
#include <sstream>
#include <string>
#include <utility> // For std::pair

using namespace std;

const int INF = 999;

typedef vector<vector<int>> matrix;

void floid(int n, matrix &D, matrix &P) {
    // Floyd-Warshall algorithm with 1-indexed vertices
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k; // Store the intermediate vertex (1-indexed)
                }
            }
        }
    }
}

vector<int> get_path(int u, int v, const matrix &D, const matrix &P) {
    if (D[u][v] == INF) return {}; // No path exists
    
    if (u == v) return {u}; // Self-loop
    
    vector<int> path;
    
    // Helper function to reconstruct the path from u to v
    function<void(int, int)> reconstruct = [&](int start, int end) {
        int k = P[start][end]; // Get intermediate vertex
        
        if (k == 0) { // Direct edge or no intermediate vertex
            path.push_back(start); // Add source vertex
            if (start != end) // Don't add destination twice if same as source
                path.push_back(end); // Add destination vertex
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
    
    int n, m;
    ss >> n >> m;
    
    // Initialize matrices (using 1-indexed)
    matrix D(n+1, vector<int>(n+1, INF));
    matrix P(n+1, vector<int>(n+1, 0)); // 0 means direct edge or no path
    
    // Set diagonal (distance from vertex to itself) to 0
    for (int i = 1; i <= n; i++) {
        D[i][i] = 0;
    }
    
    // Read the edges
    for (int i = 0; i < m; i++) {
        int u, v, w;
        ss >> u >> v >> w;
        // Already 1-indexed in input
        D[u][v] = w;
        // P[u][v] = 0; // Direct edge (already set to 0 by default)
    }
    
    int k;
    ss >> k;
    
    vector<pair<int, int>> queries(k);
    for (int i = 0; i < k; i++) {
        int s, e;
        ss >> s >> e;
        // Already 1-indexed in input
        queries[i] = {s, e};
    }
    
    // Run Floyd-Warshall algorithm
    floid(n, D, P);
    
    // Output distance matrix
    cout << "D matrix:" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << D[i][j] << (j == n ? "\n" : " ");
        }
    }
    
    // Output predecessor matrix
    cout << "\nP matrix:" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << P[i][j] << (j == n ? "\n" : " ");
        }
    }
    
    // Output paths for queries
    cout << "\nPaths for queries:" << endl;
    for (auto [u, v] : queries) {
        vector<int> path = get_path(u, v, D, P);
        cout << "Path from " << u << " to " << v << ": ";
        if (path.empty()) {
            cout << "NONE\n";
        } else {
            for (int i = 0; i < path.size(); i++)
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