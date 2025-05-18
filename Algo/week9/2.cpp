#include <iostream>
#include <vector>
using namespace std;

// Global variables
vector<int> w;       // Input weights
vector<bool> include; // Tracks which elements are included in the current subset
vector<vector<int>> solutions; // Store all solutions
int n;               // Number of elements
int W;               // Target sum

// Function to check if continuing with current state is promising
bool promising(int i, int weight, int total) {
    return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}

// Backtracking function to find subsets with sum equal to W
void sum_of_subsets(int i, int weight, int total) {
    if (promising(i, weight, total)) {
        if (weight == W) {
            // Found a solution, store the included elements
            vector<int> solution;
            for (int j = 1; j <= i; j++) {
                if (include[j]) {
                    solution.push_back(w[j]);
                }
            }
            solutions.push_back(solution);
        } else {
            // Try including w[i+1]
            include[i + 1] = true;
            sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);
            
            // Try excluding w[i+1]
            include[i + 1] = false;
            sum_of_subsets(i + 1, weight, total - w[i + 1]);
        }
    }
}

int main() {
    // Read input
    // freopen("2.txt", "r", stdin);
    cin >> n >> W;
    
    // Resize and initialize arrays
    w.resize(n + 1);
    include.resize(n + 1, false);
    solutions.clear();
    
    // Read weights
    int total = 0;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        total += w[i];
    }
    
    // Find all subsets with sum W
    sum_of_subsets(0, 0, total);
    
    cout << solutions.size() << endl;

    // Print each solution
    for (const auto& solution : solutions) {
        if (!solution.empty()) {
            cout << solution[0];  // Print first number without a space before it
            
            // Print remaining numbers with a space before each
            for (size_t i = 1; i < solution.size(); i++) {
                cout << " " << solution[i];
            }
        }
        cout << endl;
    }
    
    return 0;
}
    