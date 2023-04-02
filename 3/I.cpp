/*
 * Нетрудно заметить, что...
 *
 * Давайте будем смотреть машинки, с которыми хочет поиграть Петя, по очереди.
 * Понятно, что если такая машинка (с таким номером) уже стоит на полу, ты мы ничего не делаем.
 * Если такая машинка еще не на полу, и для нее есть там место, то мы снимаем ее с полки и ставим на пол.
 * (понятно, что нам нужно постоянно иметь на полу как можно больше машинок)
 * Но что же делать, если такой машинки на полу нет, а места не хватает. Очевидно, нужно убрать какую-то машинку на полку.
 * Какую же? Ну видимо ту, что нужна будет как можно дальше или вообще не нужна.
 *
 * Таким образом, нам необходимо уметь отслеживать текущие "приоритеты" машинок, то есть следующие моменты, когда эти машинки должны быть на полу.
 * А также уметь ранжировать машинки на полу по их приоритетам, чтобы находить самую "ненужную".
 * Кажется, с этим прекрасно справится vector<queue<?>> (приоритеты) и set<?> (хранить машинки на полу).
 *
 * Оценка сложности: O(NlogN)
 * Оценка памяти: O(N+P+K)
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int main() {

    int32_t n, k, p;
    cin >> n >> k >> p;

    static vector<queue<int64_t>> priorities(n+1);
    vector<int32_t> cars;

    int32_t cur, last = 0;
    for (int64_t i = 0; i < p; ++i) {
        cin >> cur;
        if (cur != last) {
            priorities[cur].push(i);
            cars.push_back(cur);
        }
        last = cur;
    }

    for (queue<int64_t> &item: priorities) {
        item.push(500001);
    }


    auto cmp = [](int32_t c1, int32_t c2){
        return priorities[c1].front() > priorities[c2].front();
    };
    set<int32_t, decltype(cmp)> floor(cmp);

    int32_t actions = 0;
    for (const int32_t &car : cars) {
        // if already on the floor
        auto find = floor.find(car);
        if (find != floor.end()) {
            floor.erase(find);
        }
        // if not on the floor
        else {
            // clear the floor if full
            if (floor.size() == k) floor.erase(floor.begin());
            actions++;
        }
        priorities[car].pop();
        floor.insert(car);
    }

    cout << actions;

    return 0;
}