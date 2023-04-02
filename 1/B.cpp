/*
 * Нетрудно заметить, что...
 *
 * (Идея решения данной задачи схожа с проверкой строки на правильную скобочную последовательность и ее решением с помощью стека)
 * Назовем пару символов "подходящей", если один из них является ловушкой, другой животным, для которого она предназначена (например "а" и "А")
 * Думаю это вполне очевидно, что для существования решения необходимо, чтобы в строке "зоопарка" находилась пара идущих подряд "подходящих" символов.
 * Далее, выкинем эту пару из строки и повторим предыдущую операцию.
 * Также очевидно, что для существования решения необходимо, чтобы при повторении предыдущих шагов строка "зоопарка" сократилась до пустой.
 * А для составления ответа будем каждую ловушку помечать индексом животного, вместе с которым мы ее вычеркнули.
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>
#include <vector>

using namespace std;

struct letter {
    char c;
    size_t index;
};

int main() {
    string zoo;
    cin >> zoo;
    vector<letter> stack;
    vector<size_t> traps;
    size_t animal_counter = 0;
    for (char c : zoo) {
        // trap
        if (c >= 'A' && c <= 'Z') {
            if (stack.empty()) {
                letter current = {c, traps.size()};
                stack.push_back(current);
                traps.push_back(0);
                continue;
            }
            letter last = stack.back();
            char last_char = last.c;
            if (last_char >= 'a' && last_char <= 'z' && c - last_char == 'A' - 'a') {
                stack.pop_back();
                traps.push_back(last.index);
            } else {
                letter current = {c, traps.size()};
                stack.push_back(current);
                traps.push_back(0);
            }
        }
        // animal
        else {
            if (stack.empty()) {
                letter current = {c, ++animal_counter};
                stack.push_back(current);
                continue;
            }
            letter last = stack.back();
            char last_char = last.c;
            if (last_char >= 'A' && last_char <= 'Z' && last_char - c == 'A' - 'a') {
                stack.pop_back();
                traps[last.index] = ++animal_counter;
            } else {
                letter current = {c, ++animal_counter};
                stack.push_back(current);
            }
        }
    }
    if (!stack.empty()) {
        cout << "Impossible";
    } else {
        cout << "Possible" << endl;
        for (size_t trap : traps) {
            cout << trap << " ";
        }
    }
    return 0;
}