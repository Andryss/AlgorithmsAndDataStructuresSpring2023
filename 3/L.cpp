/*
 * Нетрудно заметить, что...
 *
 * Идея до жути проста и прямолинейна. Я удивлен, что она вообще прошла.
 * Давайте просто хранить помимо элементов текущего окна, также их отсортированную версию.
 *
 * Для получения нового состояния окна нам нужно будет удалить старый элемент из двух мест и вставить новый.
 * Для этого прекрасно подойдут queue<?> и set<?>
 *
 * Оценка сложности: O(NlogK)
 * Оценка памяти: O(K)
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>
#include <set>
#include <list>

using namespace std;

int main() {

    int32_t n, k;
    cin >> n >> k;

    list<int32_t> window;
    multiset<int32_t> values;

    // init window
    int32_t new_value, old_value, idx;
    for (idx = 0; idx < k; ++idx) {
        cin >> new_value;
        window.push_back(new_value);
        values.insert(new_value);
    }
    cout << *values.begin() << ' ';

    for (; idx < n; ++idx) {
        // delete old
        old_value = window.front();
        window.pop_front();
        values.erase(values.find(old_value));
        // append new
        cin >> new_value;
        window.push_back(new_value);
        values.insert(new_value);
        // print result
        cout << *values.begin() << ' ';
    }

    return 0;
}
