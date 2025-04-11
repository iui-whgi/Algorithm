
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int lcs(string x, string y) {
    int m = x.length();
    int n = y.length();

    if (m == 0 || n == 0) {
        return 0;
    }

    if (x[m - 1] == y[n - 1]) {
        return lcs(x.substr(0, m - 1), y.substr(0, n - 1)) + 1;
    } else {
        return max(lcs(x, y.substr(0, n - 1)),
                   lcs(x.substr(0, m - 1), y));
    }
}



// ? LCS B포함된거거

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

pair<vector<vector<int>>, vector<vector<int>>> lcs(string x, string y) {
    x = ' ' + x;
    y = ' ' + y;
    int m = x.size();
    int n = y.size();

    vector<vector<int>> c(m, vector<int>(n, 0));
    vector<vector<int>> b(m, vector<int>(n, 0));

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            if (x[i] == y[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;  // 대각선 (↖)
            } else {
                if (c[i][j - 1] > c[i - 1][j]) {
                    c[i][j] = c[i][j - 1];
                    b[i][j] = 2;  // 왼쪽 (←)
                } else {
                    c[i][j] = c[i - 1][j];
                    b[i][j] = 3;  // 위쪽 (↑)
                }
            }
        }
    }

    return {c, b};
}






pair<vector<vector<int>>, vector<vector<int>>> lcs(string x, string y) {
    x = ' ' + x;
    y = ' ' + y;

    int m = x.size();
    int n = y.size();   

    vector<vector<int>> c(m, vector<int>(n, 0));
    vector<vector<int>> b(m, vector<int>(n, 0));


    for (int i = 1; i < n; i++){    
        for (int j = 1; j < n; j++)
        {
            if (x[i] == y[i])
            {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = 1;
            }
            else{
                if (c[i][j-1] > c[i-1][j]){
                    c[i][j] = c[i][j-1];
                    b[i][j] = 2;
                }
                else{
                    c[i][j] = c[i-1][j];
                    b[i][j] = 3;

                }
            }
            
        }
        
    }   

    
    return {c, b};
}
