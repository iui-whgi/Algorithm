
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

int exchangesort(int n, vector<int>& S) {
    int count = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = i+1; j<= n; j++)
            if(S[i] > S[j]){
                swap(S[i], S[j]);
                count++;
            }
    }
    
    return count;
}

void binsearch(int n, vector<int>& S, int x, vector<int>& location)
{
    int low,high,mid;
    low = 0; high = n;
    location =0;
    while(low<high && location ==0){
        mid = (low+high)/2;
        
        if(x == S[mid]){
            location = mid;
        }
        else if(x < S[mid]){
            high = mid;
        }
        else{
            low = mid+1;
        }
    }
}

int main() {

    int N, M;

    cin >> N>> M;

    vector<int> arr(N);
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }
    
    vector<int> loc(M,-1);
    vector<int> arr2(M);
    for(int i=0; i<M; i++){
        cin >> arr[i];
    }

    int count = exchangesort(N-1, arr);

    for(int i=0; i<M; i++){
        binsearch(N-1, arr, arr2[i], loc);
    }

    for (int i = 0; i< M ; i++) {
        int x = arr[i];
        bool Found = false;
        for (int j = 0; j < N; j++){
            if (arr[j] == x){
                cout << x << " is in " << j+1 << "." <<endl;
                Found = true;
                break;
            }
        }
        if(!Found){
            cout << x << " is not in S." << endl;
        }

    }
    
}