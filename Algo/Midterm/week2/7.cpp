
#include <bits/stdc++.h>
using namespace std;

void hanoi(int n, char src, char via, char dst, int *count) {
    (*count)++;
    if (n == 1) {
    }
    else {
        hanoi(n-1, src, dst, via,count);
        hanoi(1, src, via, dst,count);
        hanoi(n-1, via, src, dst,count);

        // hanoi(n-1, src, via, dst,count);
        // hanoi(1, src, dst, via,count);
        // hanoi(n-1, via, dst, via,count);
    }
}


long long getTotalMoves(int n) {
    return (1LL << n) - 1; // 2^n - 1
}

pair<char, char> findKthMove(int n, char src, char via, char dst, long long k) {
    if (n == 1) {
        return {src, dst};
    }
    
    long long moves = getTotalMoves(n-1); 
    // ! 여기가 정말중요
    
    if (k <= moves) {
        return findKthMove(n-1, src, dst, via, k);
    } 
    else if (k == moves + 1) {
        return {src, dst};
    } 
    else if ( k > moves){
        return findKthMove(n-1, via, src, dst, k - moves - 1);
    }
}

int main() {
    int n, count = 0;
    long long k;
    
    cin >> n >> k;
    
    pair<char, char> result = findKthMove(n, 'A', 'B', 'C', k);
    
    cout << result.first << " -> " << result.second << endl;
    
    
    hanoi(n, 'A', 'B', 'C', &count);
    cout << count << endl;
    
    return 0;
}






