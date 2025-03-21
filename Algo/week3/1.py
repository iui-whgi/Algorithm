#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 전역변수로 찾는 횟수를 저장할 Count 선언
int Count = 0;

// 이진 탐색 함수
int binsearch2(const vector<int>& arr, int low, int high, int key) {
    Count++;

    if (low > high)
        return -1; // 값을 찾지 못했을 때 -1 반환

    int mid = (low + high) / 2;

    if (key == arr[mid])
        return mid;
    else if (key < arr[mid])
        return binsearch2(arr, low, mid - 1, key);
    else
        return binsearch2(arr, mid + 1, high, key);
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> array(N);
    for (int i = 0; i < N; i++) {
        cin >> array[i];
    }

    sort(array.begin(), array.end());

    vector<int> keys(M);
    for (int i = 0; i < M; i++) {
        cin >> keys[i];
    }

    for (int i = 0; i < M; i++) {
        Count = 0;
        int location = binsearch2(array, 0, N - 1, keys[i]);
        cout << Count << " " << location << "\n";
    }

    return 0;
}
