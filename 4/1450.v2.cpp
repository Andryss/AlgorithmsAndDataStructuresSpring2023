/*
 * Нетрудно заметить, что...
 *
 * Суть задачи: найти максимальный путь (по весу) в ориентированном ациклическом графе из одной вершины в другую.
 *
 * Попытка 2: алгоритм Беллмана-Форда
 *
 * Интуиция: будем перебирать все ребра Ai->Bi и смотреть, если проход по этому ребру увеличивает расстояние до Bi, то обновим расстояние до Bi.
 *
 * На самом деле:
 * Рассмотрим все максимальные пути из start в i, содержащие n ребер (по количеству вершин). Это пути из n-1 ребра, к которым добавлено какое-то ребро.
 * Значит зная все пути из n-1 ребра не составит труда найти все пути из n ребер.
 * Для n=0 максимальное расстояние будет равно -inf для всех вершин, кроме start.
 *
 * Оценка сложности: O(N*M)
 * Оценка памяти: O(N+M)
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>
#include <vector>

using namespace std;

/*
 * Bellman–Ford Algorithm
 * time complexity: O(n*m)
 * time: 0.39
 * space complexity: O(n+m)
 * space: 2 432 КБ
 */

struct connection {
    int16_t from;
    int16_t to;
    int32_t weight;
};

int main() {
    int16_t n; int32_t m;
    cin >> n >> m;

    vector<connection> connections;
    int16_t from, to, weight;
    while (m --> 0) {
        cin >> from >> to >> weight;
        connections.push_back({from, to, weight});
    }

    int16_t start, finish;
    cin >> start >> finish;

    vector<int32_t> distances(n+1, -1e9);
    distances[start] = 0;

    while (true) {
        bool is_any_change = false;

        for (const connection& connection : connections) {
            if (distances[connection.from] + connection.weight > distances[connection.to]) {
                distances[connection.to] = distances[connection.from] + connection.weight;
                is_any_change = true;
            }
        }

        if (!is_any_change) break;
    }

    if (distances[finish] > 0) {
        cout << distances[finish];
    } else {
        cout << "No solution";
    }

    return 0;
}
