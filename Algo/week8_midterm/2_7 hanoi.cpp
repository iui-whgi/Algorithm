


#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;

int cnt = 0;


int getTotalmoves(int n){
    return (1LL << n) -1;
}


pair<char,char> findKthMove(int n , char src, char via, char dst, int k){
    int moves = getTotalmoves(n-1);

    if( k <= moves) return findKthMove(n-1, src,dst,via ,k);
    else if(k == moves+1) return {src,dst};
    else if(k > moves) return findKthMove(n-1, via, src, dst , k-moves-1);

}

void hanoi(int n , char src, char via, char dst){
    cnt++;
    
    if (n == 1) {
        return;
    }
    hanoi(n-1, src, dst , via);
    hanoi(1, src, via, dst);
    hanoi(n-1, src, via, dst);
    

}

int main(){

    int n , k;

    cin >> n >> k;

    pair<char, char> result = findKthMove(n,'A','B','C' ,k);

    hanoi(n,'A','B','C');

    

    cout << result.first << "->" << result.second << endl << cnt;
    



}