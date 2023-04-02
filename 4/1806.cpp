/*
 * Нетрудно заметить, что...
 *
 * Суть задачи: найти кратчайший путь в графе от одной вершины до другой
 * Казалось, задача проста. Но нет. Основная проблема состоит в том, чтобы понять между какими вершинами есть ребра и какой у них вес.
 * Конечно, можно попробовать перебрать всевозможные пары вершин и проверить каждую пару на наличие ребра и установить вес.
 * Перебор всех пар вершин имеет сложность O(N^2), но не сложно заметить, что оценка скорости моего алгоритма лучше.
 * Давайте подумаем, как можно улучшить ситуацию.
 *
 * Заметим, что номера телеграфов состоят только из 10 цифр. И что нам это дает? Несложно оценить, то каждый телеграф имеет максимум 135 возможных соседей.
 * И для каждого телеграфа мы можем их запросто вычислить и сопоставить им время передачи.
 * Тогда перебор всех пар вершим можно заменить на генерацию всех соседей для каждой вершины и проверку наличия их среди исходных данных.
 * Такой алгоритм будет иметь сложность O(N*ln(N)) при использовании set или вообще O(N) при использовании unordered_set. Ого! Так скоро и до O(1) дойти можно.
 *
 * Таким образом мы за O(N) можем построить весь граф и останется только найти в нем кратчайший путь от Анки до Чапаева.
 *
 * (Думаю алгоритм Дейкстры всем знаком и не нуждается в представлении, но для полной картины мира приведу его обоснование.
 * Присваиваем каждой вершине число - кратчайшее расстояние до нее от начальной вершины. Изначально у начальной 0, у остальных +inf.
 * На каждом шаге выбираем непомеченную вершину с наименьшим расстоянием, так как его мы уже никак не улучшим при условии наличия только положительных ребер.
 * Помечаем эту вершину и пытаемся улучшить расстояния до непомеченных вершин смежных с ней. Продолжаем эти шаги до тех пор, пока не пометим все вершины.
 * В конченом итоге каждая вершине сопоставляется число - кратчайшее расстояние до нее от начальной вершины либо +inf в случае недостижимости.
 * По сути говоря алгоритм похож на обход в ширину, который происходит по весу ребер от наименьших к наибольшим)
 *
 * Оценка сложности: O(N*ln(N))
 * Оценка памяти: O(N)
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

static vector<string> neighbors(135);
static vector<int32_t> weights(135);
static vector<int16_t> cost_with_prefix(10);

inline void fill_neighbors_weights() {
    int p = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            weights[p++] = cost_with_prefix[i];
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = i+1; j < 10; j++) {
            weights[p++] = cost_with_prefix[i];
        }
    }
}

inline void fill_neighbors_of(string tel) {
    int p = 0;
    for (int i = 0; i < 10; i++) {
        for (int8_t j = '0'; j <= '9'; j++) {
            if (tel[i] == j) continue;
            neighbors[p] = tel;
            neighbors[p][i] = j;
            p++;
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = i+1; j < 10; j++) {
            neighbors[p] = tel;
            swap(neighbors[p][i], neighbors[p][j]);
            p++;
        }
    }
}

int main() {

    int32_t n;
    cin >> n;

    // read prefix costs
    for (int i = 0; i < 10; ++i) cin >> cost_with_prefix[i];
    // fill neighbors weights
    fill_neighbors_weights();

    // read tels
    vector<string> tel_of_node(n+1);
    unordered_map<string,int32_t> node_of_tel;

    string tel;
    for (int32_t i = 1; i <= n; ++i) {
        cin >> tel;
        tel_of_node[i] = tel;
        node_of_tel[tel] = i;
    }


    // create table of cur min distances (dijkstra)
    int32_t inf = 1<<30;
    vector<int32_t> distances(n+1, inf);
    vector<int32_t> last_nodes(n+1);
    auto comp = [
            /* MAIN THING */
            &
            /* DON'T FORGET IT PLEASE */
            distances](int32_t v1, int32_t v2) {
        return distances[v1] < distances[v2] || distances[v1] == distances[v2] && v1 < v2;
    };
    set<int32_t, decltype(comp)> not_marked(comp);

    distances[1] = 0;
    not_marked.insert(1);

    while (!not_marked.empty()) {

        // get node with in dist and it's tel
        auto first = not_marked.begin();
        int32_t node_with_min_dist = *first;
        string tel_with_min_dist = tel_of_node[node_with_min_dist];
        not_marked.erase(first);

        // "imagine" neighbors
        fill_neighbors_of(tel_with_min_dist);

        // iterate through neighbors
        for (int i = 0; i < 135; i++) {
            auto& neighbor = neighbors[i];

            auto neighbor_iter = node_of_tel.find(neighbor);
            if (neighbor_iter == node_of_tel.end()) continue;
            int32_t neighbor_node = (*neighbor_iter).second;

            if (distances[neighbor_node] > distances[node_with_min_dist] + weights[i]) {
                not_marked.erase(neighbor_node);
                distances[neighbor_node] = distances[node_with_min_dist] + weights[i];
                last_nodes[neighbor_node] = node_with_min_dist;
                not_marked.insert(neighbor_node);
            }
        }
    }

    // print answer
    if (distances[n] == inf) {
        cout << -1;
    } else {
        cout << distances[n] << endl;

        // construct path
        vector<int32_t> path;
        int32_t node = n;
        while (last_nodes[node]) {
            path.push_back(node);
            node = last_nodes[node];
        }
        path.push_back(1);

        cout << path.size() << endl;

        while (!path.empty()) {
            cout << path.back() << ' ';
            path.pop_back();
        }
    }

    return 0;
}
