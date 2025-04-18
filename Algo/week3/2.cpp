

#include <iostream>
#include <vector>
using namespace std;

// global variables
int n;
vector<int> S;
int Count = 0;

void merge2(int low, int mid, int high) {
    Count++;
    int i = low, j = mid + 1, k = 0;
    vector<int> U(high - low + 1);
    
    while (i <= mid && j <= high)
        U[k++] = (S[i] < S[j]) ? S[i++] : S[j++];
    
    if (i > mid)
        while (j <= high)
            U[k++] = S[j++];
    else // i > mid
        while (i <= mid)
            U[k++] = S[i++];
    
    // for (int t = low; t <= high; t++)
    //     S[t] = U[t - low];
    for (int t = 0; t <= high-low; t++)
        S[t+low] = U[t];
}


void mergesort2(int low, int high)
{
    
    if (low < high) {
        int mid = (low + high) / 2;
        mergesort2(low, mid);
        mergesort2(mid + 1, high);
        merge2(low, mid, high);
    }
}



int main() {
    cin >> n;
    S.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> S[i];
    
    
    mergesort2(1, n);
    
    cout << S[1];
    for (int i = 2; i <= n; i++)
        cout << " " << S[i] ;
    cout << endl;
    cout << Count << endl;
    
    return 0;

}





