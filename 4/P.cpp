/*
 * Нетрудно заметить, что...
 *
 * Назовем возможность самолета "долететь из любого города в другой (возможно, с дозаправками в пути)", как возможность "посетить все города".
 * Заметим, что если мы можем посетить все города, имея размер топливного бака CAN_MORE, то мы можем посетить все города и с любым размером бака, бОльшим CAN_MORE.
 * Также заметим и обратное, что если мы не можем посетить все города с баком CANT_LESS, то мы не можем сделать этого и с любым баком меньшим CANT_LESS.
 * Значит для решения задачи мы можем использовать бинарный поиск по размеру бака.
 *
 * Но для этого нам нужно уметь ответить на вопрос: сможем ли мы посетить все города с каким-то размером бака FUEL_TANK? Как нам это сделать?
 * Давайте представим Бубундию в виде ориентированного взвешенного графа. Уберем из него все ребра, вес которых больше, чем FUEL_TANK.
 * Теперь нужно ответить на вопрос: получился ли итоговый граф связным (то есть из каждой вершины можно пройти в каждую).
 *
 * Для этого достаточно проверить что из первой вершины все остальные достижимы и наоборот - из остальных вершин можно добраться до первой.
 * Тогда сначала пройдемся поиском в глубину от первой вершины по ребрам в их прямом направлении,
 * а потом поиском в глубину от первой вершины по ребрам в их обратном направлении. И если в обоих случаях мы обошли все вершины, то граф связный.
 *
 * Оценка сложности: O(N^2 * ln(10^9))
 * Оценка памяти: O(N^2)
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static int16_t n;
static vector<vector<int32_t>> costs;

static auto is_true = [](bool val){ return val; };

void dfs_forward(int16_t i, vector<bool>& visited, int32_t capacity) {
    visited[i] = true;
    for (int16_t j = 0; j < n; ++j) {
        if (!visited[j] && costs[i][j] <= capacity && i != j) {
            dfs_forward(j, visited, capacity);
        }
    }
}

void dfs_backward(int16_t i, vector<bool>& visited, int32_t capacity) {
    visited[i] = true;
    for (int16_t j = 0; j < n; ++j) {
        if (!visited[j] && costs[j][i] <= capacity && i != j) {
            dfs_backward(j, visited, capacity);
        }
    }
}

bool can_visit_all(int32_t capacity) {

    vector<bool> visited_forward(n);
    dfs_forward(0, visited_forward, capacity);
    if (!all_of(visited_forward.begin(), visited_forward.end(), ::is_true)) return false;

    vector<bool> visited_backward(n);
    dfs_backward(0, visited_backward, capacity);
    return all_of(visited_backward.begin(), visited_backward.end(), ::is_true);
}

int main() {

    cin >> n;

    costs = vector<vector<int32_t>>(n, vector<int32_t>(n));


    int32_t cur, min = 1<<30, max = 0;
    for (int16_t i = 0; i < n; ++i) {
        for (int16_t j = 0; j < n; ++j) {
            cin >> cur;
            if (i == j) continue;
            max = std::max(max, cur);
            min = std::min(min, cur);
            costs[i][j] = cur;
        }
    }

    while (min < max) {
        int32_t mid = (min + max) >> 1;
        if (can_visit_all(mid)) {
            max = mid;
        } else {
            min = mid + 1;
        }
    }

    cout << max;

    return 0;
}
