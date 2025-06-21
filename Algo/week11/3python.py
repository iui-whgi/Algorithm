#!/usr/bin/env python3
import sys
import heapq
from typing import List

sys.stdin = open('3.txt', 'r')    # ← 필요하면 주석 해제

INF_VAL = 0xFFFF        # = 65 535
N_nodes = 0             # 전역 변수 (도시 수)
adj_matrix: List[List[int]] = []

min_length_global = INF_VAL
optimal_tour_global: List[int] = []


def print_path_vector(p: List[int]) -> None:
    """경로 벡터 공백 구분 출력(마지막 공백 없음)"""
    print(" ".join(map(str, p)), end='')


class Node:
    """우선순위 큐에 넣을 노드"""
    __slots__ = ("level", "bound", "path")

    def __init__(self, level: int, bound: int, path: List[int]):
        self.level = level
        self.bound = bound
        self.path = path

    # heapq는 최소 힙이므로 __lt__가 “더 작다 = 우선순위 높다”가 되도록 정의
    def __lt__(self, other: "Node") -> bool:
        if self.bound != other.bound:
            return self.bound < other.bound
        if len(self.path) != len(other.path):
            return len(self.path) < len(other.path)
        return self.path < other.path    # 사전식 비교


def calculate_tour_length(tour_path: List[int]) -> int:
    """완전한 투어의 실제 길이(불가능하면 INF_VAL)"""
    if len(tour_path) < 2:
        return INF_VAL
    current_len = 0
    for u, v in zip(tour_path, tour_path[1:]):
        w = adj_matrix[u][v]
        if w == INF_VAL:
            return INF_VAL
        current_len += w
        if current_len >= INF_VAL:
            return INF_VAL
    return current_len


def calculate_bound(node_v: Node) -> int:
    """
    Branch‑and‑Bound용 휴리스틱 하한(bound) 계산.
    C++ 버전 로직을 그대로 옮김.
    """
    current_cost = 0
    p = node_v.path

    # 현재까지 경로의 실제 비용
    for u, v in zip(p, p[1:]):
        w = adj_matrix[u][v]
        if w == INF_VAL:
            return INF_VAL
        current_cost += w
        if current_cost >= INF_VAL:
            return INF_VAL

    # 남은 정점에 대해 ‘최소 간선’ 추정
    est_remain = 0
    in_path = [False] * (N_nodes + 1)
    for city in p:
        in_path[city] = True

    last = p[-1]

    for city in range(1, N_nodes + 1):
        # 이미 지나간 도시 & 마지막 노드가 아니면 생략
        if in_path[city] and city != last:
            continue

        min_edge = INF_VAL
        if city == last:
            if len(p) == N_nodes:            # 경로가 모든 도시에 도달
                min_edge = adj_matrix[city][1]
            else:
                for nxt in range(1, N_nodes + 1):
                    if not in_path[nxt]:
                        min_edge = min(min_edge, adj_matrix[city][nxt])
        else:
            for nxt in range(1, N_nodes + 1):
                if city == nxt:
                    continue
                if (not in_path[nxt]) or nxt == 1:
                    min_edge = min(min_edge, adj_matrix[city][nxt])

        if min_edge == INF_VAL:
            return INF_VAL
        if est_remain > INF_VAL - min_edge:
            return INF_VAL
        est_remain += min_edge

    if current_cost > INF_VAL - est_remain:
        return INF_VAL
    return current_cost + est_remain


def find_remaining_vertex(p: List[int]) -> int:
    """아직 방문하지 않은 첫 번째 정점(없으면 −1)"""
    visited = [False] * (N_nodes + 1)
    for node in p:
        visited[node] = True
    for i in range(1, N_nodes + 1):
        if not visited[i]:
            return i
    return -1


def print_node_details(level: int, val: int, path: List[int]) -> None:
    """디버깅·출력용: level, bound/길이, 경로"""
    val_str = "INF" if val == INF_VAL else str(val)
    print(f"{level} {val_str} ", end='')
    print_path_vector(path)
    print()


def travel2_revised() -> None:
    global min_length_global, optimal_tour_global

    pq: List[Node] = []

    min_length_global = INF_VAL
    optimal_tour_global = []

    root = Node(level=0, bound=0, path=[1])
    root.bound = calculate_bound(root)
    print_node_details(root.level, root.bound, root.path)

    if root.bound < min_length_global:
        heapq.heappush(pq, root)

    while pq:
        v = heapq.heappop(pq)

        if v.bound >= min_length_global:
            continue  # 더 탐색할 가치 없음

        for city in range(1, N_nodes + 1):
            if city in v.path:
                continue

            u_path = v.path + [city]
            u_level = v.level + 1
            u = Node(level=u_level, bound=0, path=u_path)

            # 하나 남은 경우(마지막 정점 찾기)
            if u_level == N_nodes - 2:
                tour = u_path + [find_remaining_vertex(u_path), 1]
                tour_len = calculate_tour_length(tour)
                print_node_details(u.level, tour_len, tour)

                if tour_len < min_length_global:
                    min_length_global = tour_len
                    optimal_tour_global = tour

            elif u_level == N_nodes - 1:
                tour = u_path + [1]
                tour_len = calculate_tour_length(tour)
                print_node_details(u.level, tour_len, tour)

                if tour_len < min_length_global:
                    min_length_global = tour_len
                    optimal_tour_global = tour

            else:
                u.bound = calculate_bound(u)
                print_node_details(u.level, u.bound, u.path)
                if u.bound < min_length_global:
                    heapq.heappush(pq, u)


def main() -> None:
    global N_nodes, adj_matrix

    M_edges = 0
    N_nodes, M_edges = map(int, sys.stdin.readline().split())

    # 인접 행렬 초기화
    adj_matrix = [[INF_VAL] * (N_nodes + 1) for _ in range(N_nodes + 1)]

    for _ in range(M_edges):
        u, v, w = map(int, sys.stdin.readline().split())
        adj_matrix[u][v] = w

    if N_nodes == 1:
        print_node_details(0, 0, [1])
        print(0)
        print(1)
        return

    travel2_revised()

    print("INF" if min_length_global == INF_VAL else min_length_global)
    if optimal_tour_global:
        print_path_vector(optimal_tour_global)
        print()


if __name__ == "__main__":
    main()
