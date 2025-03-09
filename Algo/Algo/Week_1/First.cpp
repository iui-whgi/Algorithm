
#include <iostream>
#include <vector>

using namespace std;


int main() {

    int N,M;

    cin >> N >> M;

    vector<int> arr(N);
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }

    vector<int> SearchV(M);
    for (int i = 0; i < M; i++)
    {
        cin >> SearchV[i];
    }
    
    

    for (int i = 0; i< M ; i++) {
        int x = SearchV[i];
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