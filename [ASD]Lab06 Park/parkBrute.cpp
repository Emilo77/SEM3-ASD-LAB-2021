#include <iostream>
#include <vector>
#include <queue>

using std::vector;

int checkPath(vector<vector<int>> &glade, int index, int distance) {
    std::queue<std::pair<int, int>> que;
    int actualDistance = 0;
    vector<bool> visited(glade.size());

    que.push({index, actualDistance});
    visited.at(index) = true;

    int actual;
    while (!que.empty()) {
        actual = que.front().first;
        actualDistance = que.front().second;
        if (actualDistance == distance) {
            return actual;
        }

        int vecSize = glade.at(actual).size();

        for (int i = 0; i < vecSize; i++) {
            if (!visited.at(glade.at(actual).at(i))) {
                que.push({glade.at(actual).at(i), actualDistance + 1});
            }
            visited.at(glade.at(actual).at(i)) = true;
        }
        que.pop();
    }
    return -1;

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    vector<vector<int>> glade(n + 1);
    int a, b;
    for (int i = 0; i < n; i++) {
        std::cin >> a;
        std::cin >> b;
        if (a != -1) {
            glade.at(i + 1).push_back(a);
            glade.at(a).push_back(i + 1);
        }
        if (b != -1) {
            glade.at(i + 1).push_back(b);
            glade.at(b).push_back(i + 1);
        }
    }
    long m;
    std::cin >> m;
    int index = 0;
    int distance = 0;

    for (int i = 0; i < m; i++) {
        std::cin >> index;
        std::cin >> distance;
        if (distance == 0) {
            std::cout << index;
        } else {
            std::cout << checkPath(glade, index, distance) << std::endl;
        }
    }
    return 0;


}
//8
//3 4
//-1 6
//2 5
//-1 -1
//7 -1
//-1 -1
//8 -1
//-1 -1
//6
//1 3
//1 4
//1 5
//6 1
//6 4
//6 5


