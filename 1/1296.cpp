/*
 * Нетрудно заметить, что...
 *
 * Задачу можно представить, как автомат с двумя состояниями.
 * Первое состояние будет отображать сумму ряда на данный момент, а второе - максимальную сумму подпоследовательности до текущего элемента.
 * Соответственно каждое новое первое состояние будет вычисляться, как максимум между значением предыдущего состояния + текущий элемент и текущим элементом.
 * Проще говоря, каждый новый элемент будет либо находиться в середине какой-то цепочки, либо будет ее началом.
 * А второе состояние будет вычисляться, как максимум между предыдущим значением второго состояние и текущим значение первого.
 * А ответом будет конечное значение второго состояния.
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>

using namespace std;

int main() {
    int32_t n;
    cin >> n;
    int32_t cur, sum = 0, max_sum = 0;
    for (int32_t i = 0; i < n; i++) {
        cin >> cur;
        sum = max(sum + cur, cur);
        max_sum = max(max_sum, sum);
    }
    cout << max_sum;
    return 0;
}