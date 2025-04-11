#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int binSearch(const vector<int>& arr, int num, int low, int high) {
    if (low > high) return -1;
    int mid = (low + high) / 2;
    if (arr[mid] == num)
        return mid;
    else if (num < arr[mid])
        return binSearch(arr, num, low, mid - 1);
    else
        return binSearch(arr, num, mid + 1, high);
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end()); // 정렬 필수

    for (int i = 0; i < m; i++) {
        int num;
        cin >> num;
        int result = binSearch(arr, num, 0, n - 1);
        if (result != -1)
            cout << num << " is in " << result + 1 << "." << endl;
        else
            cout << num << " is not in S." << endl;
    }

    return 0;
}


