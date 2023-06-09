/*
 * Нетрудно заметить, что...
 *
 * Давайте для начала предположим, что контейнера и ограничения в 0 бактерий не существует.
 * Тогда количество бактерий после некоторого дня будет вычисляться, как a'' = a' * b - c (где a' - изначальное количество бактерий на текущий день).
 * Для последующего дня количество бактерий a''' = a'' * b - c. И по аналогии далее.
 * Не сложно заметить, что если a'' < a', то a''' < a'' и так далее по аналогии.
 * Аналогично если a'' == a', то a''' == a'' и далее. А также если a'' > a', то a''' > a'' и далее.
 * Так можно утверждать, поскольку коэффициенты b и с не меняются, меняется только лишь a'.
 * А теперь на сцену выходит контейнер и ограничение в 0 бактерий. Что нам это дает? Да то, что теперь a' ограничено между 0 и d.
 * Теперь же, если a' < a'' < a''' < ... , то эта последовательность не вырастет больше d.
 * То есть, начиная с какого-то элемента все последующие будут равны между собой и равны d.
 * И аналогично, если a' > a'' > a''' > ... , то эта последовательность не упадет ниже 0 и, начиная с какого-то элемента, все последующие будут равны 0.
 * Тогда, давайте вычислять количество бактерий либо до тех пор, пока количество дней не станет равно k, либо до тех пор, пока эти количества не будут равны.
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>

using namespace std;

int main() {
    int16_t a, b, c, d;
    int64_t k;
    cin >> a >> b >> c >> d >> k;

    int32_t cur = a, next;
    for (int64_t i = 0; i < k; i++) {
        next = cur * b - c;
        if (next < 0) {
            cur = 0;
            break;
        }
        if (next > d) next = d;
        if (next == cur) break;
        cur = next;
    }

    cout << cur;

    return 0;
}