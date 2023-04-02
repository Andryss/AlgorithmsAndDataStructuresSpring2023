#include <iostream>
#include <deque>

using namespace std;

int main() {
    int32_t n;
    cin >> n;

    deque<int32_t> first;
    deque<int32_t> second;

    size_t fs = first.size();
    size_t ss = second.size();

    char command;
    int32_t goblin;
    for (; n > 0; --n) {
        cin >> command;
        if (command == '-') {
            int32_t front = first.front();
            cout << front << endl;
            if (fs == ss) {
                first.push_back(second.front());
                first.pop_front();
                second.pop_front();
                ss--;
            } else {
                first.pop_front();
                fs--;
            }
            continue;
        }
        cin >> goblin;
        if (command == '+') {
            if (fs == ss) {
                second.push_back(goblin);
                first.push_back(second.front());
                second.pop_front();
                fs++;
            } else {
                second.push_back(goblin);
                ss++;
            }
        } else { // command == '*'
            if (fs == ss) {
                first.push_back(goblin);
                fs++;
            } else {
                second.push_front(goblin);
                ss++;
            }
        }
    }
    return 0;
}