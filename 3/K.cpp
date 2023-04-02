/*
 * Нетрудно заметить, что...
 *
 * За 1 секунду 180 Гб памяти? Готовсь... Цельсь... malloc...
 * Задача точь-в-точь третья лабораторная по языкам программирования.
 *
 * Идея такова: храним описание блоков память в виде связного списка.
 * Каждый блок памяти содержит информацию о своей занятости, начало и конец, а также ссылки на соседей.
 * Когда нам нужно выделить новый блок, мы пробегаемся по всем с начала в поисках первого подходящего. И если находим, то пытаемся разбить блок на 2 кусочка.
 * Если все удается, то резервируем блок.
 *
 * А когда просят освободить блок, то стоит после его освобождения попытаться "склеить" его с соседями, чтобы блоки не делились до единичных.
 * Идея проста, но есть одна малюсенька проблема. И эта проблема - время.
 * Ну тогда давайте хранить свободные блоки, отсортированные по количеству свободного места в них, а при запросе доставать первый подходящий.
 * Для этого прекрасно подходит старый добрый set<?>.
 *
 * Оценка сложности: O(MlogN)
 * Оценка памяти: O(N)
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct block {
    struct block *prev;
    struct block *next;
    bool is_free;
    int32_t start;
    int32_t end;
};

static auto cmp = [](struct block* b1, struct block* b2){
    int32_t b1_size = b1->end - b1->start, b2_size = b2->end - b2->start;
    return b1_size < b2_size || b1_size == b2_size && b1->start < b2->start;
};
static set<struct block*, decltype(cmp)> free_sorted(cmp);


static void connect(struct block* prev, struct block* next) {
    if (prev != nullptr) prev->next = next;
    if (next != nullptr) next->prev = prev;
}

static block min_to_find = {nullptr, nullptr, false, 0, 0};
static struct block* find_first_free(int32_t query) {
    min_to_find.end = query;
    auto upper = free_sorted.lower_bound(&min_to_find);
    struct block* current = (upper == free_sorted.end() ? nullptr : *upper);
    if (current != nullptr) free_sorted.erase(current);
    return current;
}

static void try_split(struct block* blk, int32_t query) {
    if (blk->end - blk->start <= query) return;
    int32_t border = blk->start + query;
    auto* next = new block{nullptr, nullptr, true, border, blk->end};
    free_sorted.insert(next);
    blk->end = border;
    connect(next, blk->next);
    connect(blk, next);
}

static struct block* heap_malloc(int32_t query) {
    struct block* candidate = find_first_free(query);
    if (candidate == nullptr) return nullptr;
    try_split(candidate, query);
    candidate->is_free = false;
    return candidate;
}

static void try_merge(struct block* blk) {
    struct block* prev = blk->prev;
    if (prev != nullptr && prev->is_free) {
        free_sorted.erase(prev);
        connect(prev->prev, blk);
        blk->start = prev->start;
        delete prev;
    }
    struct block* next = blk->next;
    if (next != nullptr && next->is_free) {
        free_sorted.erase(next);
        connect(blk, next->next);
        blk->end = next->end;
        delete next;
    }
}

static void heap_free(struct block* blk) {
    if (blk == nullptr || blk->is_free) return;
    blk->is_free = true;
    try_merge(blk);
    free_sorted.insert(blk);
}


int main() {
    int32_t n, m;
    cin >> n >> m;
    auto* heap = new block{nullptr, nullptr, true, 0, n};
    free_sorted.insert(heap);
    vector<block*> queries(m);

    int32_t query;
    struct block* allocated;
    for (int32_t i = 0; i < m; ++i) {
        cin >> query;
        if (query > 0) {
            allocated = heap_malloc(query);
            if (allocated == nullptr) {
                cout << -1 << endl;
                continue;
            }
            queries[i] = allocated;
            cout << (allocated->start + 1) << endl;
        } else {
            heap_free(queries[-query - 1]);
        }
    }

//    delete heap;

    return 0;
}
