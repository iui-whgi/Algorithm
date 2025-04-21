


#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef vector<vector<int>> matrix;


void quadEncoder(matrix& arr,int n){

    bool flag = true;
    int temp = arr[0][0];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(temp!=arr[i][j]){
                flag = false;
            }
        }
    }

    if(flag==true){
        cout << (temp == 1 ? "b" : "w");    
    }
    else{
        cout << "x";
        matrix a(n/2,vector<int>(n/2,0));
        matrix b(n/2,vector<int>(n/2,0));
        matrix c(n/2,vector<int>(n/2,0));
        matrix d(n/2,vector<int>(n/2,0));
    
        for (int i = 0; i < n/2; i++)
        {
            for (int j = 0; j < n/2; j++)
            {
                a[i][j] = arr[i][j];
                b[i][j] = arr[i][n/2+j];
                c[i][j] = arr[n/2+i][j];
                d[i][j] = arr[n/2+i][n/2+j];
            }
        }
        quadEncoder(a,n/2);
        quadEncoder(b,n/2);
        quadEncoder(c,n/2);
        quadEncoder(d,n/2);

    }




    
    
    
}


int main(){
    int n;

    cin  >> n;
    
    matrix m(n,vector<int>(n,0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> m[i][j];
        }
    }
    quadEncoder(m,n);

}