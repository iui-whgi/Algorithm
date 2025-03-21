
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

int BubbleSort(int n, vector<int>& arr) {
    int count = 0;
    for (size_t i = 0; i <= n; i++)
    {
        for (size_t j = i+1; j<= n; j++)
            if(arr[i] > arr[j]){
                swap(arr[i], arr[j]);
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

    int count = BubbleSort(N, arr);
    

    for(int i=0; i<N; i++){
        cout << arr[i] << " ";
    }

    cout <<  "\n" << count << endl;

    return 0;

}