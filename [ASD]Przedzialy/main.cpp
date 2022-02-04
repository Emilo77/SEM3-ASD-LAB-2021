#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;

    cin >> n >> m;

    char c;
    int l, r;
    set<int> setStart;
    set<int> setEnd;

    int minValueEnd = n + 1;
    int maxValueStart = 0;

    for (int i = 0; i < m; i++) {
        cin >> c >> l >> r;

        if (c == '+') {
            if(l == 1) {
                if(setStart.find(r) == setStart.end()) {
                    setStart.insert(r);
                    if(r > maxValueStart) {
                        maxValueStart = r;
                    }
                }
            } else {
                if(setEnd.find(l) == setEnd.end()) {
                    setEnd.insert(l);
                    if(l < minValueEnd) {
                        minValueEnd = l;
                    }
                }
            }
        } else {
            if(l == 1) {
                if(setStart.find(r) != setStart.end()) {
                    setStart.erase(r);
                    if(r == maxValueStart && !setStart.empty()) {
                        maxValueStart = *setStart.rbegin();
                    } else if (setStart.empty()) {
                        maxValueStart = 0;
                    }
                }
            } else {
                if(setEnd.find(l) != setEnd.end()) {
                    setEnd.erase(l);
                    if(l == minValueEnd && !setEnd.empty()) {
                        minValueEnd = *setEnd.begin();
                    } else if (setEnd.empty()) {
                        minValueEnd = n + 1;
                    }
                }
            }
        }

        if(minValueEnd <= maxValueStart) {
            cout << 0 << endl;
        } else {
            cout << minValueEnd - maxValueStart - 1 << endl;
        }

    }
}

//10 9
//+ 1 2
//+ 1 6
//+ 7 10
//- 1 2
//+ 1 9
//+ 1 6
//- 1 6
//- 1 1
//- 1 9
