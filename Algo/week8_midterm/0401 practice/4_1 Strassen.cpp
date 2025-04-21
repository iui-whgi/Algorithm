
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef vector<vector<int>> Matrix;


void strassen(Matrix& a, Matrix& b, Matrix& result, int k){

    

}


int main(){
    int n ,  k;

    cin >> n >> k;
    
    Matrix a(n, vector<int>(n,0));
    Matrix b(n, vector<int>(n,0));
    Matrix result(n, vector<int>(n,0));

    strassen(a,b, result, k);
    

    

    
}