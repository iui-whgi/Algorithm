

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;    
int  n;
vector<int> S;

int Cnt = 0;

void partition(int low, int high, int& pivotpoint){

    int pivotitem = low;
    int j = low;
    for (int i = low+1; i <= high; i++)
    {
        if(S[i] < S[pivotitem]){
            j++;
            Cnt++;
            swap(S[i],S[j]);
        }
    }
    

    pivotpoint = j;
    Cnt++;
    swap(S[low],S[pivotpoint]);
    
}


void quicksort(int low, int high){
    int pivot;
    
    if(low < high){
        partition(low, high, pivot);
        quicksort(low, pivot-1);
        quicksort(pivot+1, high);

    }
}


int main(){

    cin >> n;
    S.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> S[i];
    quicksort(1, n);

    cout << S[1];
    for (int i = 2; i <= n; i++)
        cout << " " << S[i];
    cout << endl << Cnt << endl;
    return 0;
}