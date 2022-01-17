#include <iostream>
#include <algorithm>
#include <map>
#include <queue>


using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::map;
using std::queue;
using std::endl;

void restartVisited(vector<bool> &visited) {
    unsigned int size = visited.size();
    for (int i = 0; i < size; i++) {
        visited.at(i) = false;
    }
}

void printResult(int closest, int maxEnergy, vector<int> powerRes, vector<int>
path) {

    if (maxEnergy < 0) {
        cout << -1;

    } else {
        cout << closest << " " << maxEnergy << " " << powerRes.size() << endl;

        for (int i = 0; i < closest; i++) {
            cout << path.at(i) << " ";
        }
        cout << endl;
        if (!powerRes.empty()) {
            for (int powerRe: powerRes) {
                cout << powerRe << " ";
            }
        } else cout << endl;
    }
}


int closestPath(vector<vector<int>> &roads, queue<pair<int, int>> &que,
                vector<bool> &visited, int end) {
    que.push({1, 0});
    visited.at(1) = true;
    while (que.front().first != end && !que.empty()) {
        int key = que.front().first;
        int value = que.front().second;
        if (!roads.at(key).empty()) {
            unsigned long vecsize = roads.at(key).size();
            for (int i = 0; i < vecsize; i++) {
                if (!visited.at(roads.at(key).at(i))) {
                    que.push({roads.at(key).at(i), value + 1});
                }
                visited.at(roads.at(key).at(i)) = true;
            }
        }
        que.pop();

    }
    if (que.empty()) {
        return -1;
    } else return que.front().second;
}

vector<int> findClosestPath(vector<vector<int>> &roads,
                            queue<int> &que, vector<bool> &
visited, int end, vector<pair<int, int>> &result) {

    visited.at(1) = true;
    que.push(1);
    while (que.front() != end && !que.empty()) {
        int key = que.front();
        if (!roads.at(key).empty()) {
            unsigned long vecsize = roads.at(key).size();
            for (int i = 0; i < vecsize; i++) {
                if (!visited.at(roads.at(key).at(i))) {
                    que.push(roads.at(key).at(i));
                    result.emplace_back(key, roads.at(key).at(i));
                }

                visited.at(roads.at(key).at(i)) = true;
            }
        }
        que.pop();
    }
    vector<int> path;
    if (!result.empty()) {
        long resultSize = result.size();
        while (result.at(resultSize - 1).second != end) {
            result.pop_back();
            resultSize--;
        }

        long index = resultSize - 1;
        int trafficNum = result.at(index).second;
        int previous = trafficNum;

        while (previous != 1) {
            if (trafficNum == previous) {
                path.push_back(result.at(index).second);
                previous = result.at(index).first;
            }
            index--;
            if (index >= 0) {
                trafficNum = result.at(index).second;
            }
        }
        path.push_back(1);
        std::reverse(path.begin(), path.end());
    }
    return path;
}

int findBestEnergy(vector<bool> forbiddenValues,
                   vector<vector<int>> &possibleEnergy,
                   vector<vector<pair<bool, bool>>> &alreadyInserted, int
                   roadNumber, int batteryCapacity, int costBetween,
                   vector<int> &powerBanks, vector<int> &result, vector<int>
                   path) {

    possibleEnergy.resize(roadNumber + 1);
    alreadyInserted.resize(roadNumber + 2);
    for (int i = 0; i < roadNumber + 2; i++) {
        alreadyInserted.at(i).resize(5002);
        pair<bool, bool> newPair = {false, false};
        std::fill(alreadyInserted.at(i).begin(), alreadyInserted.at(i).end(),
                  newPair);

    }
    possibleEnergy.at(1).push_back(batteryCapacity);
    alreadyInserted.at(1).at(batteryCapacity) = {true, false};

    int index = 2;
    while (index < roadNumber + 1) {
        unsigned previousVectorSize = possibleEnergy.at(index - 1).size();
        for (int i = 0; i < previousVectorSize; i++) {
            int previousEnergy = possibleEnergy.at(index - 1).at(i);
            int actualEnergy = previousEnergy - costBetween;
            if (actualEnergy >= 0) {
                if (!alreadyInserted.at(index).at(actualEnergy).first) {
                    possibleEnergy.at(index).push_back(actualEnergy);
                    alreadyInserted.at(index).at(actualEnergy).first = true;
                    alreadyInserted.at(index).at(actualEnergy).second = false;
                }
            }
            int actualFueledEnergy = actualEnergy + powerBanks.at(index);
            if (actualEnergy >= 0 && actualFueledEnergy <=
                                     batteryCapacity) {
                if (!forbiddenValues.at(actualFueledEnergy) &&
                    !alreadyInserted.at(index).at(actualFueledEnergy).first) {
                    possibleEnergy.at(index).push_back(actualFueledEnergy);
                    alreadyInserted.at(index).at(
                            actualFueledEnergy).first = true;
                    alreadyInserted.at(index).at(actualFueledEnergy).second =
                            true;
                }
            }
        }
        index++;
    }

    if (possibleEnergy.at(roadNumber).empty()) {
        return -1;
    } else {
        int endValue = -1;
        int endValuesSize = possibleEnergy.at(roadNumber).size();
        int fueledCount = 0;
        for (int i = 0; i < endValuesSize; i++) {
            if (possibleEnergy.at(roadNumber).at(i) > endValue) {
                endValue = possibleEnergy.at(roadNumber).at(i);
            }
        }
        int maxEndEnergy = endValue;
        int actualValue = endValue;
        int previousValue;
        for (int i = roadNumber; i > 0; i--) {
            if (alreadyInserted.at(i).at(actualValue).second) {
                previousValue = actualValue + costBetween - powerBanks.at(i);
                result.push_back(path.at(i - 1));
                fueledCount++;

            } else {
                previousValue = actualValue + costBetween;
            }
            actualValue = previousValue;
        }
        if (!result.empty()) {
            std::reverse(result.begin(), result.end());
        }
        return maxEndEnergy;
    }


}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int batteryCapacity; // <1, 5000>
    int costBetween; // <0, batteryCapacity>
    int forbiddenAmount; // <0, batteryCapacity + 1>

    vector<bool> forbiddenValues;
    forbiddenValues.resize(5005);
    std::fill(forbiddenValues.begin(), forbiddenValues.end(), false);

    cin >> batteryCapacity >> costBetween >> forbiddenAmount;

    for (int i = 0; i < forbiddenAmount; i++) {
        int temp;
        cin >> temp;
        forbiddenValues.at(temp) = true;
    }

    int trafficNumber; // 2 <= trafficNumber <= 1000
    int roadNumber; // 1 <= roadNumber <= 100 000

    cin >> trafficNumber >> roadNumber;

    vector<vector<int>> roads;
    roads.resize(100001);
    for (int i = 0; i < roadNumber; i++) {
        int inputRoad;
        int outputRoad;
        cin >> inputRoad >> outputRoad;
        roads.at(inputRoad).push_back(outputRoad);
        roads.at(outputRoad).push_back(inputRoad);
    }


    if (trafficNumber == 1) {
        cout << 1 << batteryCapacity << 0 << endl;
        cout << 1 << endl;
        cout << endl;
        return 0;
    }

    vector<int> powerBanks;
    vector<bool> visited;
    vector<pair<int, int>> result;


    powerBanks.push_back(0);
    for (int i = 0; i < trafficNumber; i++) {
        int temp;
        cin >> temp;
        powerBanks.push_back(temp);
        visited.push_back(false);
    }
    visited.push_back(false);
    visited.push_back(false);

    std::queue<pair<int, int>> que;
    vector<int> path;

    int closest = closestPath(roads, que, visited, trafficNumber) + 1;

    if (closest == 0) {
        cout << -1;
        return 0;
    }

    restartVisited(visited);

    std::queue<int> que2;

    path = findClosestPath(roads, que2, visited, trafficNumber, result);

    if (path.empty()) {
        cout << -1;
        return 0;
    }
    if (!roads.empty()) {
        roads.clear();
        roads.shrink_to_fit();
    }

    vector<vector<int>> possibleEnergy;
    vector<int> powerRes;
    vector<vector<pair<bool, bool>>> alreadyInserted;
    int maxEnergy;

    maxEnergy = findBestEnergy(forbiddenValues, possibleEnergy, alreadyInserted,
                               closest, batteryCapacity, costBetween,
                               powerBanks, powerRes, path);


    printResult(closest, maxEnergy, powerRes, path);

    return 0;
}

//7 2 5
//5 7 0 2 1
//9 9
//1 2
//6 7
//3 7
//8 9
//2 6
//1 5
//3 8
//7 8
//3 6
//0 3 4 3 2 3 5 7 4