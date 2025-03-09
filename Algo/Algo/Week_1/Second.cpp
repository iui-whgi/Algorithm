
#include <iostream>
#include <vector>

using namespace std;

int sumArrayElements(const vector<int>& arr) {
    int sum = 0;
    for (int element : arr) {
        sum += element;
    }
    return sum;
}




int main() {

    int N;

    cin >> N;

    int sum = 0;

    vector<int> arr(N);
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }
    
    int result = sumArrayElements(arr);
    

    cout << result << endl;

    return 0;

}