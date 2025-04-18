
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;





void binsearch(vector<int>&arr,int search, int low, int high){

    int mid = (low+high)/2;

    if(low>high) {
        cout << 0 <<endl;
        return ;
    }
    

    if(arr[mid] == search){
        cout << mid+1 << endl;
    }
    else if(arr[mid]< search){
        binsearch(arr, search, mid+1, high);
    }
    else
        binsearch(arr, search, low, mid-1);

    


}



int main(){

    int n, m;

    cin >> n >> m;

    vector<int> arr (n,0);
    vector<int> searchV (m,0);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    
    sort(arr.begin(), arr.end()); // 꼭 정렬해야 함!

    for (int i = 0; i < m; i++)
    {
        cin >> searchV[i];
    

    }


    for (int i = 0; i < m; i++)
    {

        binsearch(arr, searchV[i], 0, n-1);

    }



}