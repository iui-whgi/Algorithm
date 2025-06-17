def promising(i, weight, total):
    return (weight + total >= W) and (weight == W or weight + w[i + 1] <= W)

def sum_of_subsets(i, weight, total):
    if promising(i, weight, total):
        if weight == W:
            solution = [w[j] for j in range(1, i + 1) if include[j]]
            solutions.append(solution)
        else:
            include[i + 1] = True
            sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1])
            
            include[i + 1] = False
            sum_of_subsets(i + 1, weight, total - w[i + 1])

# 메인 함수 역할
if __name__ == "__main__":
    # 파일에서 입력 읽기
    with open("2.txt", "r") as f:
        lines = f.readlines()
    
    n, W = map(int, lines[0].split())
    w = [0] + list(map(int, lines[1].split()))  # 인덱스 1부터 시작하게 0 추가
    include = [False] * (n + 1)
    total = sum(w[1:])
    solutions = []

    sum_of_subsets(0, 0, total)

    print(len(solutions))
    for solution in solutions:
        print(" ".join(map(str, solution)))
