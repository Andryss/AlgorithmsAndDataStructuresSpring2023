#include <iostream>
#include <vector>

using namespace std;

int main() {
    int32_t n;
    cin >> n;

    int32_t cur, max = 0;

    vector<int32_t> stack;

    while (n --> 0) {
        cin >> cur;
        if (max < cur) {
            while (++max < cur) {
                stack.push_back(max);
            }
        } else {
            if (stack.back() != cur) {
                cout << "Cheater";
                return 0;
            }
            stack.pop_back();
        }
    }
    cout << "Not a proof";
    return 0;
}