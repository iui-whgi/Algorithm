#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

#define INF_VAL 0xFFFF

int N_nodes;
std::vector<std::vector<int>> adj_matrix;
int min_length_global;
std::vector<int> optimal_tour_global;

void print_path_vector(const std::vector<int>& p) {
    for (size_t i = 0; i < p.size(); ++i) {
        std::cout << p[i] << (i == p.size() - 1 ? "" : " ");
    }
}

struct Node {
    int level;
    int bound;
    std::vector<int> path;

    bool operator>(const Node& other) const {
        if (bound != other.bound) {
            return bound > other.bound;
        }
        if (path.size() != other.path.size()) {
            return path.size() > other.path.size();
        }
        return path > other.path;
    }
};

int calculate_tour_length(const std::vector<int>& tour_path) {
    int current_len = 0;
    if (tour_path.size() < 2) return INF_VAL;
    for (size_t i = 0; i < tour_path.size() - 1; ++i) {
        int u_node = tour_path[i];
        int v_node = tour_path[i+1];
        if (adj_matrix[u_node][v_node] == INF_VAL) {
            return INF_VAL;
        }
        current_len += adj_matrix[u_node][v_node];
    }
    if (current_len >= INF_VAL) return INF_VAL;
    return current_len;
}

int calculate_bound(const Node& node_v) {
    int current_path_actual_cost = 0;
    if (node_v.path.size() > 1) {
        for (size_t i = 0; i < node_v.path.size() - 1; ++i) {
            if (adj_matrix[node_v.path[i]][node_v.path[i+1]] == INF_VAL) {
                return INF_VAL;
            }
            current_path_actual_cost += adj_matrix[node_v.path[i]][node_v.path[i+1]];
        }
    }
    if (current_path_actual_cost >= INF_VAL) return INF_VAL;
    int estimated_remaining_cost = 0;
    std::vector<bool> is_in_current_path(N_nodes + 1, false);
    for (int city : node_v.path) {
        is_in_current_path[city] = true;
    }
    int last_node_in_path = node_v.path.back();
    for (int current_city = 1; current_city <= N_nodes; ++current_city) {
        if (is_in_current_path[current_city] && current_city != last_node_in_path) {
            continue;
        }
        int min_edge_for_current_city = INF_VAL;
        if (current_city == last_node_in_path) {
            if (node_v.path.size() == (size_t)N_nodes) { 
                min_edge_for_current_city = adj_matrix[current_city][1];
            } else {
                for (int next_city = 1; next_city <= N_nodes; ++next_city) {
                    if (!is_in_current_path[next_city]) {
                        min_edge_for_current_city = std::min(min_edge_for_current_city, adj_matrix[current_city][next_city]);
                    }
                }
            }
        } else {
            for (int next_city = 1; next_city <= N_nodes; ++next_city) {
                if (current_city == next_city) continue;
                if (!is_in_current_path[next_city] || next_city == 1) {
                    min_edge_for_current_city = std::min(min_edge_for_current_city, adj_matrix[current_city][next_city]);
                }
            }
        }
        if (min_edge_for_current_city == INF_VAL) return INF_VAL;
        if (estimated_remaining_cost > INF_VAL - min_edge_for_current_city) {
            return INF_VAL;
        }
        estimated_remaining_cost += min_edge_for_current_city;
    }
    if (current_path_actual_cost > INF_VAL - estimated_remaining_cost) return INF_VAL;
    return current_path_actual_cost + estimated_remaining_cost;
}

int find_remaining_vertex(const std::vector<int>& p) {
    std::vector<bool> visited(N_nodes + 1, false);
    for (int node_in_path : p) {
        visited[node_in_path] = true;
    }
    for (int i = 1; i <= N_nodes; ++i) {
        if (!visited[i]) {
            return i;
        }
    }
    return -1;
}

void print_node_details(int level, int bound_or_len, const std::vector<int>& path_to_print) {
    std::cout << level << " ";
    if (bound_or_len == INF_VAL) {
        std::cout << "INF ";
    } else {
        std::cout << bound_or_len << " ";
    }
    print_path_vector(path_to_print);
    std::cout << std::endl;
}

void travel2_revised() {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    min_length_global = INF_VAL;
    optimal_tour_global.clear();
    Node v_root;
    v_root.level = 0;
    v_root.path.push_back(1);
    v_root.bound = calculate_bound(v_root);
    print_node_details(v_root.level, v_root.bound, v_root.path);
    if (v_root.bound < min_length_global) {
        pq.push(v_root);
    }
    while(!pq.empty()) {
        Node current_node_v = pq.top();
        pq.pop();
        if (current_node_v.bound >= min_length_global) {
            continue;
        }
        for (int i = 1; i <= N_nodes; ++i) {
            bool is_city_i_in_path = false;
            for (int city_in_path : current_node_v.path) {
                if (city_in_path == i) {
                    is_city_i_in_path = true;
                    break;
                }
            }
            if (is_city_i_in_path) continue;
            Node child_node_u;
            child_node_u.level = current_node_v.level + 1;
            child_node_u.path = current_node_v.path;
            child_node_u.path.push_back(i);
            if (child_node_u.level == N_nodes - 2) {
                std::vector<int> tour_path_u = child_node_u.path;
                int remaining_city = find_remaining_vertex(tour_path_u);
                if (remaining_city != -1) {
                    tour_path_u.push_back(remaining_city);
                }
                tour_path_u.push_back(1);
                int tour_len = calculate_tour_length(tour_path_u);
                print_node_details(child_node_u.level, tour_len, tour_path_u);
                if (tour_len < min_length_global) {
                    min_length_global = tour_len;
                    optimal_tour_global = tour_path_u;
                }
            } else {
                if (child_node_u.level == N_nodes - 1) {
                    std::vector<int> tour_path_u = child_node_u.path;
                    tour_path_u.push_back(1);
                    int tour_len = calculate_tour_length(tour_path_u);
                    print_node_details(child_node_u.level, tour_len, tour_path_u);
                    if (tour_len < min_length_global) {
                        min_length_global = tour_len;
                        optimal_tour_global = tour_path_u;
                    }
                } else {
                    child_node_u.bound = calculate_bound(child_node_u);
                    print_node_details(child_node_u.level, child_node_u.bound, child_node_u.path);
                    if (child_node_u.bound < min_length_global) {
                        pq.push(child_node_u);
                    }
                }
            }
        }
    }
}

int main() {
    freopen("3.txt", "r", stdin);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int M_edges;
    std::cin >> N_nodes >> M_edges;
    adj_matrix.resize(N_nodes + 1, std::vector<int>(N_nodes + 1, INF_VAL));
    for (int k = 0; k < M_edges; ++k) {
        int u, v_edge, w;
        std::cin >> u >> v_edge >> w;
        adj_matrix[u][v_edge] = w;
    }
    if (N_nodes == 1) {
        print_node_details(0, 0, {1});
        std::cout << 0 << std::endl;
        std::cout << 1 << std::endl;
    } else {
        travel2_revised();
        if (min_length_global == INF_VAL) {
            std::cout << "INF" << std::endl;
        } else {
            std::cout << min_length_global << std::endl;
        }
        if (!optimal_tour_global.empty()) {
            print_path_vector(optimal_tour_global);
            std::cout << std::endl;
        }
    }
    return 0;
}
