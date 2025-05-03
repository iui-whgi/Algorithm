#include <iostream>
#include <vector>
using namespace std;

int call_count = 0;

int fibo(int n) {


    vector<int> arr(n+1);

    arr[0] = 0;
    if (n > 0) arr[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        call_count++;
        arr[i] = arr[i-1] + arr[i-2];
        if(arr[i]>1000000){
            arr[i]=arr[i]%1000000;
        }
    }
    
    return arr[n];
}

int main() {
    int n;
    cin >> n;
    
    int result = fibo(n);

    cout << result <<endl ;

}


