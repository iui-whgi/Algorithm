def promising(i, adj, vcolor):
    for j in range(1, i):
        if adj[i][j] and vcolor[i] == vcolor[j]:
            return False
    return True

def m_coloring(i, m, N, adj, vcolor, totalWays):
    if i > N:
        totalWays[0] += 1
        return

    for color in range(1, m + 1):
        vcolor[i] = color
        if promising(i, adj, vcolor):
            m_coloring(i + 1, m, N, adj, vcolor, totalWays)
        vcolor[i] = 0  # backtrack

def main():
    with open("3.txt", "r") as f:
        lines = f.readlines()

    N, M = map(int, lines[0].split())
    adj = [[False] * (N + 1) for _ in range(N + 1)]
    vcolor = [0] * (N + 1)

    for line in lines[1:1+M]:
        u, v = map(int, line.split())
        adj[u][v] = adj[v][u] = True

    minColors = 1
    while True:
        totalWays = [0]
        m_coloring(1, minColors, N, adj, vcolor, totalWays)
        if totalWays[0] > 0:
            break
        minColors += 1

    print(minColors)
    print(totalWays[0])

if __name__ == "__main__":
    main()


