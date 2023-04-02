/*
 * Нетрудно заметить, что...
 *
 * https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform
 *
 * Рассмотрим поближе процесс "шифрования" исходного слова, а именно таблицу N×N.
 * Сделаем следующую операцию: выполним циклический сдвиг каждой строки влево. То есть были столбцы c1, c2, ..., cN-1, cN, а стали c2, c3, ..., cN, c1.
 * Далее упорядочим полученные строки в лексикографическом порядке (далее просто "отсортированы" или "упорядочены"). Очевидно, что мы получим исходную таблицу.
 * Однако, давайте посмотрим, что стало с символами первого столбца. Очевидно, они перешли в последний столбец и перемешались.
 * Но символы, имеющие одинаковое значение остались в столбце в том же порядке.
 * То есть если бы мы рассмотрели символы "A" первого столбца изначально, а также после циклического сдвига и сортировки,
 * то они остались в таком же порядке друг с другом.
 * Почему так произошло?
 * Потому что изначально символы "А" в первом столбце были упорядочены друг с другом по второму символу.
 * После сдвига второй символ стал первым. И мы отсортировали строки (то есть они упорядочились по новому первому символу).
 * Символы "А" в последнем столбце все еще упорядочены по тем же символам (которые после сдвига перешли в первый столбец).
 * К чему же такое замечание?
 * Давайте сделаем следующее: возьмем символы последнего столбца и пронумеруем их индексами по порядку. А потом отсортируем без смены мест одинаковых символов.
 * Что же мы получим? А мы получим первый столбец нашей таблицы N×N, где каждый символ помечен еще каким-то индексом.
 * Почему первый столбец? Да потому что каждый столбец это все символы исходного слова, а все строки отсортированы. Значит иначе мы первый столбец не получим.
 * Что нам дают индексы?
 * Поскольку мы знаем, что одинаковые символы между собой не менялись, то каждый символ своим индексом говорит, на какое место он сместился в последнем столбце.
 * Это конечно круто, но смысл то в чем?
 * Поскольку все строки это циклические перестановки исходной, то все символы в каждой строке имеют тот же порядок, что и в исходном слове.
 * Значит следующие символы исходной строки, идущие за символами последнего столбца это - символы первого столбца. БИНГО!
 * Итого, что мы получили. У нас есть символы первого столбца, где каждый из них имеет индекс - место, на котором он стоит в последнем столбце.
 * Значит, чтобы получить следующий символ исходной строки, нужно знать первый символ той строки, на которую указывает индекс. СНОВА БИНГО!
 * Иными словами, возьмем элемент i (символ + индекс), следующий символ исходной строки будет находиться в этом же массиве по индексу, который записан в i.
 * Осталось только определить, с какого символа начать. А точно! У нас же дано число n - номер строки с исходным словом в таблице N×N.
 * Вот с него и начнем строить.
 * (Идея выглядит очень сложно, хотя реализация идет в десять строк)
 *
 * P.S.
 * За время решения данной задачи я узнал, что наисложнейшая задача на тимусе имеет сложность более 20000.
 * Сложность же этой задачи - 266. Хотя до момента отправки решения мне казалось, что число было другое...
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

void count_sort(vector<pair<char,int32_t>> &array) {
    vector<queue<int32_t>> indexes(128);
    for (const auto &el : array) {
        indexes[el.first].push(el.second);
    }
    int32_t idx = 0;
    for (int8_t i = 0x41; i < 0x7B; ++i) {
        while (!indexes[i].empty()) {
            array[idx].first = i;
            array[idx++].second = indexes[i].front();
            indexes[i].pop();
        }
    }
}

int main() {
    int32_t n;
    cin >> n;

    string letters;
    cin >> letters;

    vector<pair<char,int32_t>> indexes(letters.size());
    for (int32_t i = 0; i < letters.size(); ++i) {
        indexes[i] = {letters[i], i};
    }

    count_sort(indexes);

    int32_t cur = n - 1;
    string result;
    while (result.size() != letters.size()) {
        result += indexes[cur].first;
        cur = indexes[cur].second;
    }

    cout << result;

    return 0;
}
