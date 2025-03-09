def matrix_multiplication():
    import sys
    input = sys.stdin.read
    data = input().splitlines()

    index = 0
    N = int(data[index])  # 행렬 개수이자 행렬 크기
    index += 1

    # 첫 번째 행렬 입력
    result = [list(map(int, data[i].split())) for i in range(index, index + N)]
    index += N

    for _ in range(N - 1):
        # 다음 행렬 입력
        matrix = [list(map(int, data[i].split())) for i in range(index, index + N)]
        index += N

        # 행렬 곱셈 수행
        new_result = [[0] * N for _ in range(N)]
        for i in range(N):
            for j in range(N):
                new_result[i][j] = sum(result[i][k] * matrix[k][j] for k in range(N))

        result = new_result  # 결과 갱신

    # 결과 출력
    for row in result:
        print(" ".join(map(str, row)))

if __name__ == "__main__":
    matrix_multiplication()
