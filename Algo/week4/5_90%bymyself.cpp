


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


typedef vector<vector<int>> Matrix;



void Decoder(const string& card, int n, Matrix& A, int& index){
    
    char currentChar = card[index++];
    int color = 0;

    if(currentChar == 'x'){
        Matrix A11 = Matrix(n/2, vector<int>(n/2, 0));
        Matrix A12 = Matrix(n/2, vector<int>(n/2, 0));
        Matrix A21 = Matrix(n/2, vector<int>(n/2, 0));
        Matrix A22 = Matrix(n/2, vector<int>(n/2, 0));

        for(int i = 0; i < n/2; i++){
            for(int j = 0; j < n/2; j++){
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j+n/2];
                A21[i][j] = A[i+n/2][j];
                A22[i][j] = A[i+n/2][j+n/2];
            }
        }

        Decoder(card, n/2, A11, index);
        Decoder(card, n/2, A12, index);
        Decoder(card, n/2, A21, index);
        Decoder(card, n/2, A22, index);

        for (int i = 0; i < n/2; i++) {
            for (int j = 0; j < n/2; j++) {
                A[i][j] = A11[i][j];
                A[i][j + n/2] = A12[i][j];
                A[i + n/2][j] = A21[i][j];
                A[i + n/2][j + n/2] = A22[i][j];
            }
        }
        
    }
    else{
        if(currentChar == 'w') color = 0;
        else color = 1;


        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A[i][j] = color;
            }
        }



    }
    
    

}

int main(){
    
    int n;
    string card;

    cin >> n;
    cin >> card;
    int index = 0;

    
    
    Matrix A(n, vector<int>(n , 0));

    Decoder(card, n, A , index);
    

    cout << n << endl;

    for (int i = 0; i < n; i++)
    {
        cout << A[i][0];
        for (int j = 1; j < n; j++)
        {
            cout << " " << A[i][j];
        }
        cout << endl;
        
    }




    return 0;

}