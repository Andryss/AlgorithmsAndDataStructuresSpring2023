/*
 * Нетрудно заметить, что...
 *
 * Суть задачи: найти максимальный путь (по весу) в ориентированном ациклическом графе из одной вершины в другую.
 *
 * Попытка 3: топологическая сортировка
 *
 * Интуиция: расположим вершины друг за другом так, чтобы все ребра были слева направо и обойдем все вершины слева направо обновляя веса
 *
 * На самом деле:
 * Поскольку граф ациклический, то мы можем расположить все ребра друг за другом в ряд так, чтобы все ребра были слева направо.
 * (Берем вершину, в которую не входят ребра, добавляем ее в список. Удаляем все ребра выходящие из нее. Повторяем алгоритм, пока не положим все вершины)
 * Дальше поступаем следующим образом: стартовой вершине присваиваем максимальное расстояние 0, а остальным -inf.
 * Идем по топологически отсортированным вершинам и обновляем максимальное расстояние, до вершин, достижимых из текущей.
 * Таким образом, когда мы дойдем до какой-то вершины, мы уже точно знаем, что ее текущее расстояние максимально и увеличиться уже не может.
 *
 * Оценка сложности: O(N+M)
 * Оценка памяти: O(N+M)
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>
#include <vector>

using namespace std;

/*
 * Topological sort
 * time complexity: O(n+m)
 * time: 0.406
 * space complexity: O(n+m)
 * space: 2 224 КБ
 */

vector<vector<pair<int16_t,int32_t>>> connections;

void topological(int16_t i, vector<bool>& visited, vector<int16_t>& stack) {
    visited[i] = true;
    for (const auto& neighbor : connections[i]) {
        if (!visited[neighbor.first]) topological(neighbor.first, visited, stack);
    }
    stack.push_back(i);
}

int main() {
    int16_t n; int32_t m;
    cin >> n >> m;

    connections = vector<vector<pair<int16_t,int32_t>>>(n+1);
    int16_t from, to, weight;
    while (m --> 0) {
        cin >> from >> to >> weight;
        connections[from].emplace_back(to, weight);
    }

    vector<int16_t> stack;
    vector<bool> visited(n+1);

    for (int16_t i = 1; i <= n; ++i) {
        if (!visited[i]) topological(i, visited, stack);
    }

    int32_t inf = -1;
    vector<int32_t> distances(n+1, inf);

    int16_t start, finish;
    cin >> start >> finish;

    distances[start] = 0;

    while (!stack.empty()) {
        int16_t v = stack.back();
        stack.pop_back();

        if (distances[v] != inf) {
            for (const auto &neighbor: connections[v]) {
                distances[neighbor.first] = max(distances[neighbor.first], distances[v] + neighbor.second);
            }
        }
    }

    if (distances[finish] != inf) {
        cout << distances[finish];
    } else {
        cout << "No solution";
    }

    return 0;
}