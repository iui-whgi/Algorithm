
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


int main() {

    int N;

    cin >> N;

    int sum = 0;

    vector<int> arr(N);
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }

    int count = exchangesort(N-1, arr);
    

    for(int i=0; i<N-1; i++){
        cout << arr[i] << " ";
    }
    cout << arr[N-1];

    cout << "\n"<< count << endl;

    return 0;

}