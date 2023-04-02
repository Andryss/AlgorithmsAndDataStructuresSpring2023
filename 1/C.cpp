/*
 * Нетрудно заметить, что...
 *
 * Назовем "фреймом" блок, ограниченный "{" сверху и "}" снизу (можно сказать, что все входные данные тоже находятся внутри фрейма).
 * Давайте для каждого фрейма запоминать, какие переменные были в нем модифицированы (или просто инициализированы).
 * Таким образом, когда мы попадаем в новый фрейм (строка "{") мы создаем новый "блок для запоминания".
 * Пока мы находимся внутри фрейма, блок для запоминания постепенно заполняется новыми переменными.
 * А на выходе из фрейма (строка "}") все "запомненные" переменные откатим к состоянию, которое было у них до входа в этот фрейм.
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    unordered_map<string,vector<string>> variables;
    vector<unordered_set<string>> frame;
    frame.emplace_back();
    string line;
    while (cin >> line) {
        if (line == "{") {
            frame.emplace_back();
        } else if (line == "}") {
            for (const string& variable : frame.back()) {
                variables[variable].pop_back();
            }
            frame.pop_back();
        } else {
            size_t center = line.find('=');
            string variable = line.substr(0, center);
            string value = line.substr(center + 1);
            unordered_set<string> stack_frame = frame.back();

            if (variables.find(variable) == variables.end()) {
                // not contains
                variables[variable] = vector<string>();
            }

            // if <variable>=<digit>
            if (any_of(value.begin(), value.end(), ::isdigit)) {
                if (stack_frame.find(variable) != stack_frame.end())
                    variables[variable].pop_back();
                variables[variable].push_back(value);
                frame.back().insert(variable);
            }
            // if <variable>=<variable>
            else {
                string val;
                // if <variable>=<unknown_variable>
                if (variables.find(value) == variables.end() || variables[value].empty()) {
                    val = "0";
                }
                // if <variable>=<seen_variable>
                else {
                    val = variables[value].back();
                }

                if (stack_frame.find(variable) != stack_frame.end())
                    variables[variable].pop_back();
                variables[variable].push_back(val);
                frame.back().insert(variable);
                cout << val << endl;
            }
        }
    }
    return 0;
}