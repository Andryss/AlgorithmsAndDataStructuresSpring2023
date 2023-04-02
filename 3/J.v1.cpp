/*
 * Нетрудно заметить, что...
 *
 * Ну давайте подумаем, что нам нужно уметь делать. Нам нужно уметь хранить очередь из гоблинов с возможностью:
 * быстро добавить гоблина в середину/конец, быстро достать гоблина из начала.
 * Что может быстро с этим справится? Правильно, собственная реализация двусвязного списка с отслеживаем середины.
 * И вуаля! Perfetto!
 * Осталось только не ошибиться в реализации.
 *
 * P.S. Я не знал, что list реализует связный список...
 *
 * Оценка сложности: O(N)
 * Оценка памяти: O(N)
 *
 * Реализация идеи предлагается читателю в качестве несложного упражнения...
 */

#include <iostream>

using namespace std;

class linked_list {
private:
    struct node {
        int32_t val;
        node* next;
        node* prev;
    };

    node *head = nullptr;
    int32_t size = 0;
    node *before_center = nullptr;

    static node* create_node(int32_t value) {
        node* new_node = static_cast<node *>(malloc(sizeof(struct node)));
        new_node->val = value;
        return new_node;
    }

    static void free_node(node* node) {
        free(node);
        node = nullptr;
    }

    static void connect(node* prev, node* next) {
        prev->next = next;
        next->prev = prev;
    }

public:
    void push_center(int32_t value) {
        node* new_node = create_node(value);

        if (head == nullptr) {
            head = new_node;
            connect(head, head);
            before_center = head;
        } else {
            connect(new_node, before_center->next);
            connect(before_center, new_node);
        }

        if ((++size & 1) == 1) {
            before_center = before_center->next;
        }
    }

    void push_last(int32_t value) {
        node* new_node = create_node(value);

        if (head == nullptr) {
            head = new_node;
            connect(head, head);
            before_center = head;
        } else {
            connect(head->prev, new_node);
            connect(new_node, head);
        }

        if ((++size & 1) == 1) {
            before_center = before_center->next;
        }
    }

    int32_t pop_first() {
        int32_t value = head->val;

        node* old_head = head;
        if (head->next == head) {
            head = nullptr;
            before_center = nullptr;
            size = 0;
        } else {
            connect(head->prev, head->next);
            head = head->next;
            before_center = before_center->next;
            if ((--size & 1) == 0) {
                before_center = before_center->prev;
            }
        }
        free_node(old_head);

        return value;
    }
};


int main() {
    int32_t n;
    cin >> n;

    linked_list queue;
    char command;
    int32_t goblin;
    for (; n > 0; --n) {
        cin >> command;
        if (command == '-') {
            cout << queue.pop_first() << endl;
            continue;
        }
        cin >> goblin;
        if (command == '+') {
            queue.push_last(goblin);
        } else {
            queue.push_center(goblin);
        }
    }

    return 0;
}
