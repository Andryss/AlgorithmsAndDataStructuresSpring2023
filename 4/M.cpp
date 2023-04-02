/*
 * Нетрудно заметить, что...
 *
 * Для нахождения минимального времени поступим следующим образом: для каждой достижимой клетки найдем минимальное время прохода до него.
 *
 * Для этого примем время начальной точки за 0, а остальных за бесконечность.
 * Далее начнем обходить карту при помощи обхода в ширину. Для каждой посещенной клетки будем пытаться "улучшить минимальное время соседних клеток".
 * То есть если текущее минимальное время соседа больше, чем наше минимальное время плюс время прохода от нас до соседа, то обновим его время,
 * а также запустимся рекурсивно от соседа (а вдруг сможем обновить минимальное время для его соседей).
 *
 * Таким образом из-за обхода в ширину мы не будем обходить все возможные достижимые пути, а только те, что мы можем улучшить.
 * Каждую клетку посетим не более четырех раз (придя в нее со всех четырех сторон и улучшая её время каждый раз).
 *
 * Остался один вопрос: а как же нам восстановить путь до деревни?
 * Очевидно, что если деревня не достижима, то ее минимальное время не измениться. Но что делать, если ее время изменилось?
 * Сделаем следующим образом: раз время текущей вершины обновилось, значит в нее мы пришли из того соседа, чье время равно наше минус переход в соседа.
 * Таким образом, рекурсивно запускаясь до начального положения восстановим весь путь.
 *
 * Оценка сложности: O(N*M)
 * Оценка памяти: O(N*M)
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {

    // read data
    int32_t rows, cols, row_begin, col_begin, row_end, col_end;
    cin >> rows >> cols >> row_begin >> col_begin >> row_end >> col_end;

    vector<vector<int32_t>> map(rows, vector<int32_t>(cols));
    vector<vector<int32_t>> biases(rows, vector<int32_t>(cols, 1 << 28));

    char c;
    for (int32_t row = 0; row < rows; ++row) {
        for (int32_t col = 0; col < cols; ++col) {
            cin >> c;
            map[row][col] = (c == '#' ) ? (1 << 28) : (c == '.') ? 1 : 2;
        }
    }

    // do some bfs
    queue<pair<int32_t,int32_t>> queue;

    biases[row_begin-1][col_begin-1] = 0;
    queue.emplace(row_begin-1,col_begin-1);

    while (!queue.empty()) {
        pair<int32_t,int32_t> pair = queue.front(); queue.pop();
        int32_t row = pair.first, col = pair.second, length = biases[row][col];
        if (row > 0 && biases[row-1][col] > length + map[row-1][col]) {
            biases[row-1][col] = length + map[row-1][col];
            queue.emplace(row-1,col);
        }
        if (col > 0 && biases[row][col-1] > length + map[row][col-1]) {
            biases[row][col-1] = length + map[row][col-1];
            queue.emplace(row,col-1);
        }
        if (row < map.size() - 1 && biases[row+1][col] > length + map[row+1][col]) {
            biases[row+1][col] = length + map[row+1][col];
            queue.emplace(row+1,col);
        }
        if (col < map[0].size() - 1 && biases[row][col+1] > length + map[row][col+1]) {
            biases[row][col+1] = length + map[row][col+1];
            queue.emplace(row,col+1);
        }
    }

    // if not visit the endpoint
    if (biases[row_end-1][col_end-1] == (1 << 28)) {
        cout << -1;
        return 0;
    }

    // restore path
    cout << biases[row_end-1][col_end-1] << endl;
    vector<char> backward;

    int32_t row = row_end-1, col = col_end-1;
    while (row != row_begin - 1 || col != col_begin - 1) {
        int32_t prev_bias = biases[row][col] - map[row][col];
        if (row > 0 && biases[row-1][col] == prev_bias) {
            backward.push_back('S'); row--;
        } else if (col > 0 && biases[row][col-1] == prev_bias) {
            backward.push_back('E'); col--;
        } else if (row < rows - 1 && biases[row+1][col] == prev_bias) {
            backward.push_back('N'); row++;
        } else if (col < cols - 1 && biases[row][col+1] == prev_bias) {
            backward.push_back('W'); col++;
        }
    }

    // print path
    while (!backward.empty()) {
        cout << backward.back();
        backward.pop_back();
    }

    return 0;
}
