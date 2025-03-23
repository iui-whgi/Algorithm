

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000;
typedef vector<vector<int>> int;

int Pow(int A, int k) {
    int n = A.size();
    int result(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        result[i][i] = 1;
    }
    while (k > 0) {
        if (k % 2 == 1) {
            result = Multiply(result, A);
        }
        A = Multiply(A, A);
        k /= 2;
    }
    return result;

    
}


int main(){
    int N,K;
    cin >> N >> K;
    
    int A(N, vector<int>(N,0));

    for (int i = 0; i < N; i++) {
        for ( int j = 0 ; j <N ; j++) {
        cin >> A[i][j];
        
        }
    }
    int result = Pow(A,K);



}