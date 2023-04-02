/*
 * Нетрудно заметить, что...
 *
 * Давайте подумаем, как же нам так распределить бойцов, чтобы максимизировать бои. Для простоты рассмотрим случай между двумя командами.
 * В одной из команд пусть будет A человек, а во второй A + R (где A,R > 0). Текущая ситуация дает нам A * (A + R) схваток.
 * Рассмотрим последнего человека второй команды и переведем его в первую команду.
 * Тогда разбиение команд будет A + 1 на A + R - 1 и общий вклад (A + 1) * (A + R - 1) = A * (A + R) + R - 1 схваток. И это на R - 1 больше, чем было.
 * То есть, пока R - 1 > 0 (то есть R > 1) всегда имеет смысл переводить бойцов из больших команд в маленькие.
 * Из предыдущих вычислений следует, что для максимизации количества схваток, максимальная разница между всеми командами должна быть равна 1.
 * Значит всех бойцов нужно распределить по n / k бойцов в команду, а всех оставшихся (нецелых) распределить по одному в разные команды.
 * Осталось самое простое - посчитать итоговое количество схваток.
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>

using namespace std;

int main() {
    int16_t tests;
    cin >> tests;
    int32_t n, k;
    for (int16_t test = 0; test < tests; ++test) {
        cin >> n >> k;
        int32_t min_size = n / k,
            max_size = min_size + 1,
            max_size_count = n % k,
            min_size_count = k - max_size_count;
        int64_t all_count_max_size = max_size_count * (max_size_count - 1) / 2,
            all_count_min_size = min_size_count * (min_size_count - 1) / 2;
        int64_t all_fights = all_count_max_size * max_size * max_size +     // max_size fights
                all_count_min_size * min_size * min_size +                  // min_size fights
                max_size_count * max_size * min_size_count * min_size;      // inter fights
        cout << all_fights << endl;
    }
    return 0;
}
