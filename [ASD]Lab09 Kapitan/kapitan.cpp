#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;
using MapType = map<int, vector<int>>;

vector<pair<long long, long long>> cords;

bool compareX(const int &island1, const int &island2) {
    return cords.at(island1).first < cords.at(island2).first;
}

bool compareY(const int &island1, const int &island2) {
    return cords.at(island1).second < cords.at(island2).second;
}

void initAndSort(vector<int> &sortedX, vector<int> &sortedY, int n) {

    for (int i = 0; i < n; i++) {
        sortedX.at(i) = i + 1;
        sortedY.at(i) = i + 1;
    }

    std::sort(sortedX.begin(), sortedX.end(), compareY);
    std::sort(sortedX.begin(), sortedX.end(), compareX);

    std::sort(sortedY.begin(), sortedY.end(), compareX);
    std::sort(sortedY.begin(), sortedY.end(), compareY);
}

bool contains(int value, vector<int> &vec) {
    for (int i: vec) {
        if (i == value) {
            return true;
        }
    }
    return false;
}

void safePushBack(vector<int> &vec, int element) {
    if (!contains(element, vec)) {
        vec.push_back(element);
    }
}

void graphInitAndFill(MapType &graph, vector<int> &sortedX, vector<int>
&sortedY, int n) {

    for (int i = 1; i < n + 1; i++) {
        vector<int> emptyVec;
        graph.insert({i, emptyVec});
    }

    graph.at(sortedX.at(0)).push_back(sortedX.at(1));
    for (int i = 1; i < n - 1; i++) {
        graph.at(sortedX.at(i)).push_back(sortedX.at(i - 1));
        graph.at(sortedX.at(i)).push_back(sortedX.at(i + 1));
    }

    safePushBack(graph.at(sortedX.at(n - 1)), sortedX.at(n - 2));
    safePushBack(graph.at(sortedY.at(0)), sortedY.at(1));

    for (int i = 1; i < n - 1; i++) {
        safePushBack(graph.at(sortedY.at(i)), sortedY.at(i - 1));
        safePushBack(graph.at(sortedY.at(i)), sortedY.at(i + 1));
    }

    safePushBack(graph.at(sortedY.at(n - 1)), sortedY.at(n - 2));
}

long long distance(int actual, int next) {
    return min(abs(cords.at(actual).first - cords.at(next).first),
               abs(cords.at(actual).second - cords.at(next).second));
}

long long findClosestPath(MapType &graph, int n) {
    vector<long> cost(n + 2, 1000000005);
    priority_queue<pair<long, int>, vector<pair<long, int>>, greater<>> minQue;

    cost.at(1) = 0;
    minQue.push({cost.at(1), 1});
    pair<long, int> actualPair;

    while (!minQue.empty()) {
        actualPair = minQue.top();
        minQue.pop();
        for (auto next: graph.at(actualPair.second)) {
            long possibleCost = distance(actualPair.second, next);
            if (possibleCost + actualPair.first < cost.at(next)) {
                cost.at(next) = possibleCost + actualPair.first;
                minQue.push({cost.at(next), next});
            }
        }
    }

    return cost.at(n);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    long long tempX, tempY;
    cords.push_back({1000000001, 1000000001});

    for (int i = 1; i <= n; i++) {
        cin >> tempX >> tempY;
        cords.push_back({tempX, tempY});
    }

    vector<int> sortedX(n);
    vector<int> sortedY(n);


    initAndSort(sortedX, sortedY, n);

    MapType graph;

    graphInitAndFill(graph, sortedX, sortedY, n);

    long long result = findClosestPath(graph, n);
    cout << result << "\n";

    return 0;

}

//5
//2 2
//1 1
//4 5
//7 1
//6 7
