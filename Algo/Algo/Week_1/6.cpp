#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;


    vector<pair<int,int>> arr(N);
    for(int i = 0; i < N; i++){
        int x;
        cin >> x;
        arr[i] = {x, i};  
    }

    sort(arr.begin(), arr.end(), 
         [](auto &a, auto &b){
             return a.first < b.first;
         }
    );

    // cout << "S: ";
    // for(int i = 0; i < N; i++){
    //     cout << arr[i].first << " ";
    // }
    // cout << "\n";

    while(M--){
        int target;
        cin >> target;


        int left = 0;
        int right = N - 1;
        bool found = false;
        int foundIndex = -1; 

        while(left <= right){
            int mid = (left + right) / 2;
            // cout << mid <<endl;
            if(arr[mid].first == target){
                found = true;
                foundIndex = mid;
                break;
            }
            else if(arr[mid].first < target){
                left = mid + 1;
            }
            else{
                right = mid - 1;
            }
        }

        if(found){
            cout << target << " is in " << foundIndex + 1 << ".\n";
        } else {
            cout << target << " is not in S.\n";
        }
    }

    return 0;
}
