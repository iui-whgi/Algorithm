#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    int id;
    double weight;
    double profit;
    double profit_per_unit;
};

bool compare(Item a, Item b) {
    return a.profit_per_unit > b.profit_per_unit;
}

void fractionalKnapsack(const vector<Item>& sorted_items, double capacity,
                        vector<pair<double, double>>& used_items, double& total_profit) {
    total_profit = 0.0;
    used_items.clear();

    for (const Item& item : sorted_items) {
        if (capacity <= 0) break;
        if (capacity >= item.weight) {
            capacity -= item.weight;
            total_profit += item.profit;
            used_items.emplace_back(item.weight, item.profit);
        } else {
            double fraction = capacity / item.weight;
            double used_weight = item.weight * fraction;
            double used_profit = item.profit * fraction;
            total_profit += used_profit;
            used_items.emplace_back(used_weight, used_profit);
            break;
        }
    }
}

int main() {
    int N;
    freopen("1.txt", "r", stdin);
    cin >> N;

    vector<Item> items(N);
    for (int i = 0; i < N; ++i) {
        cin >> items[i].weight;
    }
    for (int i = 0; i < N; ++i) {
        cin >> items[i].profit;
    }

    for (int i = 0; i < N; ++i) {
        items[i].id = i;
        items[i].profit_per_unit = items[i].profit / items[i].weight;
    }

    int M;
    cin >> M;
    vector<double> capacities(M);
    for (int i = 0; i < M; ++i) {
        cin >> capacities[i];
    }

    for (int i = 0; i < M; ++i) {
        double total_profit;
        vector<Item> sorted_items = items;
        sort(sorted_items.begin(), sorted_items.end(), compare);

        vector<pair<double, double>> used_items;
        fractionalKnapsack(sorted_items, capacities[i], used_items, total_profit);

        cout << fixed << setprecision(0) << total_profit << "\n";
        for (auto& it : used_items) {
            cout << fixed << setprecision(0) << it.first << " " << it.second << "\n";
        }
    }

    return 0;
}
