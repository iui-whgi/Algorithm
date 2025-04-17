

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> v;



void quicksort(int s ,int h){
    if (s >= h) return;  
    
    int j=s;

    for (int i = s+1; i < h; i++){
        if(v[s] > v[i]){
            j++;
            swap(v[j],v[i]);
        }
    }
    swap(v[s],v[j]);

    quicksort(s,j-1);
    quicksort(j+1, h);

}


int main(){
    int n;

    cin >> n;
    v.resize(n,0);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    
    quicksort(0,n-1);

    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    



}