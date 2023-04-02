/*
 * Нетрудно заметить, что...
 *
 * Давайте разобьем итоговую строку на 3 части: начало + середина + конец.
 * В середину будет складывать те буквы, которых 1 штука или те, которых n > 2 в количестве n - 2.
 * То есть те буквы с которых мы можем получить прирост лишь увеличив расстояние между теми, что дают общий вес строки.
 * Соответственно все остальные буквы (которых хотя бы 2) мы расположим по одной штуке в начало и конец.
 * Очевидно, что буквы с наибольшим весом нужно ставить как можно дальше друг от друга (в начало "начала" и в конец "конца").
 * Пусть у нас есть две буквы A с весом W и две буквы B с весом W+R (где R >= 0), а середина имеет K букв.
 * Если расположить их в порядке BA...AB, то прирост будет (K + 1) * W + (K + 3) * (W + R) = (2K + 4) * W + (K + 3) * R.
 * А если в порядке AB...AB, то прирост (K + 2) * W + (K + 2) * (W + R) = (2K + 4) * W + (K + 2) * R.
 * А если в порядке AB...BA, то прирост (K + 3) * W + (K + 1) * (W + R) = (2K + 4) * W + (K + 1) * R.
 * Невооруженным глазом видно, что наилучшая тактика расположения: буквы с наибольшим весом - ближе к краям.
 * А для букв с одинаковым весом (R = 0) порядок не имеет значения, так как при его смене получим -1 в профите одной буквы и +1 в профите другой.
 * Осталось лишь отсортировать буквы по их весу и правильно распределить между серединой и парой начало-конец.
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string line;
    cin >> line;

    static vector<int32_t> biases(26);
    static vector<int16_t> counts(26);
    vector<int16_t> bias_sorted(26);
    int32_t bias;

    for (int16_t i = 0; i < 26; ++i) {
        cin >> bias;
        biases[i] = bias;
        bias_sorted[i] = i;
    }

    for (char c : line) counts[c - 'a']++;

    stable_sort(bias_sorted.begin(), bias_sorted.end(), [](int16_t p1, int16_t p2){
        return biases[p1] > biases[p2];
    });

    string start, center;

    for (int16_t index : bias_sorted) {
        if (counts[index] == 0) continue;
        if (counts[index] > 1) {
            counts[index] -= 2;
            start += (char)('a' + index);
        }
        while (counts[index]-- > 0) center += (char)(index + 'a');
    }


    cout << start << center;
    reverse(start.begin(), start.end());
    cout << start;

    return 0;
}