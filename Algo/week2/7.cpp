
// #include <bits/stdc++.h>
// using namespace std;

#include <bits/stdc++.h>
using namespace std;

void hanoi(int n, char src, char via, char dst, int *count) {
    (*count)++;
    if (n == 1) {
        // printf("%c -> %c\n", src, dst);
    }
    else {
        hanoi(n-1, src, dst, via,count);
        hanoi(1, src, via, dst,count);
        hanoi(n-1, via, src, dst,count);
    }
}

// int main() {
//     int n, count=0 ;
//     cin >> n;
//     hanoi(n, 'A', 'B', 'C', &count);
//     cout << count << endl;
//     return 0;
// }





// 하노이 탑에서 n개의 원판을 이동할 때 총 이동 횟수
long long getTotalMoves(int n) {
    return (1LL << n) - 1; // 2^n - 1
}

// k번째 이동을 찾는 함수
pair<char, char> findKthMove(int n, char src, char via, char dst, long long k) {
    // 기저 사례: 원판이 1개일 때
    if (n == 1) {
        return {src, dst};
    }
    
    // n-1개의 원판을 이동시키는 데 필요한 이동 횟수
    long long moves = getTotalMoves(n-1);
    
    // k번째 이동이 처음 n-1개의 원판을 src에서 via로 이동시키는 단계에 있는 경우
    if (k <= moves) {
        return findKthMove(n-1, src, dst, via, k);
    } 
    // k번째 이동이 가장 큰 원판을 src에서 dst로 이동시키는 단계인 경우
    else if (k == moves + 1) {
        return {src, dst};
    } 
    // k번째 이동이 나머지 n-1개의 원판을 via에서 dst로 이동시키는 단계에 있는 경우
    else {
        return findKthMove(n-1, via, src, dst, k - moves - 1);
    }
}

int main() {
    int n, count = 0;
    long long k;
    
    cin >> n >> k;
    
    pair<char, char> result = findKthMove(n, 'A', 'B', 'C', k);
    
    // 결과 출력
    cout << result.first << " -> " << result.second << endl;
    
    // 또는 원래 코드처럼 출력하려면
    // printf("%c -> %c\n", result.first, result.second);
    
    // 총 이동 횟수 출력
    hanoi(n, 'A', 'B', 'C', &count);
    cout << count << endl;
    // cout << getTotalMoves(n) << endl;
    
    return 0;
}