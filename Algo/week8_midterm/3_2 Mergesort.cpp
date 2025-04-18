

#include <iostream>
#include <vector>
using namespace std;

// global variables
int n;
vector<int> S;
int Count = 0;


void merge(int low, int high, int mid){

    Count++;
    
    vector<int> U(high-low+1,0);

    int i= low , j = mid+1 , k=0;
    
    while( i <= mid && j <= high){
        U[k++] = (S[i] < S[j]) ? S[i++] : S[j++];
    }

    if(i<=mid){
        while(i<=mid){
            U[k++] = S[i++];
        }
    }
    else if(j<=high){
        while(j<=high){
            U[k++] = S[j++];
        }
    }

    for (int i = 0; i <= high-low; i++)
    {
        S[i+low] = U[i];
    }
}

void mergesort2(int low,int high){
    if (low >= high) return;

    int mid = (low+high) / 2;

    mergesort2(low,mid);
    mergesort2(mid+1,high);
    merge(low,high,mid);

}
int main(){
    
    cin >> n;
    S.resize(n + 1);
    for (int i = 0; i < n; i++){
        cin >> S[i];
    }

    mergesort2(0,n-1);

    for (int i = 0; i < n; i++)
    {
        cout << S[i] << " ";
    }

    cout << endl << Count;
}




