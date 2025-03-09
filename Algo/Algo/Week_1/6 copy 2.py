def main():
    import sys
    input = sys.stdin.read
    data = input().splitlines()

    N, M = map(int, data[0].split())
    arr = [(int(data[i + 1]), i) for i in range(N)]

    # 정렬 수행 (값 기준 정렬)
    arr.sort(key=lambda x: x[0])

    print("S:", " ".join(str(x[0]) for x in arr))

    for i in range(M):
        target = int(data[N + 1 + i])

        left, right = 0, N - 1
        found = False
        found_index = -1

        while left <= right:
            mid = (left + right) // 2
            print(mid)  # 중간값 출력 (C++ 코드와 동일한 디버깅 출력)

            if arr[mid][0] == target:
                found = True
                found_index = arr[mid][1]
                break
            elif arr[mid][0] < target:
                left = mid + 1
            else:
                right = mid - 1

        if found:
            print(f"{target} is in {found_index + 1}.")
        else:
            print(f"{target} is not in S.")

if __name__ == "__main__":
    main()

