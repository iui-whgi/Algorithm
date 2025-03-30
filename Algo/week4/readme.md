
2번은 못풀고 있다
일단 3번은 gpt갈김. 꼭 수정해야함


4번은 거의 풀었는데 for문에 

```
        cout << "x";    

        for(int i = 0; i < n/2; i++){
            for(int j = 0; j < n/2; j++){
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j+n/2];
                A21[i][j] = A[i+n/2][j];
                A22[i][j] = A[i+n/2][j+n/2];
            }
        }

        Encode(A11, n/2);
        Encode(A12, n/2);
        Encode(A21, n/2);
        Encode(A22, n/2);

이걸 넣어버림 그래서 for문 도는동안 또 !=안맞으면 계속 돌게됨


[5_90%내가푼.cpp](./5_90%내가푼.cpp)  
4번과 유사한 문제이지만 잘풀다가 합쳐주는걸 안했음음

```

        for (int i = 0; i < n/2; i++) {
            for (int j = 0; j < n/2; j++) {
                A[i][j] = A11[i][j];
                A[i][j + n/2] = A12[i][j];
                A[i + n/2][j] = A21[i][j];
                A[i + n/2][j + n/2] = A22[i][j];
            }
        }


41-48 부분을 넣어주지를 않았음 encoder와 다르게 다시 큰 A에 반영을 해줘야하는데
그리고 void Decoder(const string& card, int n, Matrix& A, int& index) 여기서 
처음에 Matrix& A, int& index에 & 안달아줬음 A는 변경가능해야하니까 저렇게 , index는 처음에 안되서 전역변수로 돌릴려다가 전역변수는 함수안에서 지역변수 취급되기 때문에 계속 반영이 안된다하더라
