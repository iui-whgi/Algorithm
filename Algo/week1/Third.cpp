#include <iostream>
#include <vector>
using namespace std;

int sum = 0;

void exchange_sort(int n, vector<int>& S){
    
    for(int i = 1; i<=n; i++){
        for(int j=i+1; j<=n; j++){
            if(S[i] > S[j]) {
                sum +=1;
                swap(S[i], S[j]);
            }
        }
    }
    cout << S[1];
    for(int i=2; i<=n; i++){
        cout << " " <<S[i] ;
    }

}

int main(){

    int n,x,location;
    cin >> n;

    vector<int> S(n+1);

    for(int i=1; i<=n ;i++){
        cin >> S[i];
    }

    exchange_sort(n, S);
    
    cout << endl <<  sum << endl;



    return 0;
}