#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // Read the array
    vector<int> S(N);
    for(int i = 0; i < N; i++){
        cin >> S[i];
    }

    // Process each query
    for(int i = 0; i < M; i++){
        int target;
        cin >> target;
        
        // Linear search to find the position in the original array (1-indexed)
        bool found = false;
        for(int j = 0; j < N; j++){
            if(S[j] == target){
                cout << target << " is in " << j + 1 << ".\n";
                found = true;
                break;
            }
        }
        
        // If the element is not found
        if(!found){
            cout << target << " is not in S.\n";
        }
    }

    return 0;
}