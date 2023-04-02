/*
 * Было трудно заметить, что... (но я справился)
 *
 * Пускай мы получили итоговое самое большое число. Давайте рассмотрим кго, а также все кусочки из которых оно состоит.
 * Заметим, что для каждой пары кусочков i и j (где i > j) должно выполняться, что их конкатенация ij должна быть больше, чем обратная ji,
 * иначе получится, что элементы i и j можно переставить и получить большее число.
 * (как же вкусно, когда идея на 100% повторяет код)
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string line;
    vector<string> lines;
    while (cin >> line) {
        lines.push_back(line);
    }

    stable_sort(lines.begin(), lines.end(), [](auto l1, auto l2){
        return l1 + l2 > l2 + l1;
    });

    for (const string& l : lines) {
        cout << l;
    }
    return 0;
}
