#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int MAXN = 500005;
int logMAX = 20;
map<int, vector<int>> tree;
vector<int> parent(MAXN);

int abs(int x) {
    if (x < 0) return -x;
    else return x;
}

vector<int> decToBin(int x) {
    vector<int> resVec;
    int reminder;
    while (x != 0) {
        reminder = x % 2;
        resVec.push_back(reminder);
        x /= 2;
    }
    std::reverse(resVec.begin(), resVec.end());
    return resVec;
}

void setLevels(vector<int> &levelVec,
               int level, int glade) {
    levelVec.at(glade) = level;
    if (tree.at(glade).empty()) {
        return;
    }
    if (tree.at(glade).size() == 1) {
        setLevels(levelVec, level + 1, tree.at(glade).at(0));
        return;
    } else {
        setLevels(levelVec, level + 1, tree.at(glade).at(0));
        setLevels(levelVec, level + 1, tree.at(glade).at(1));
        return;
    }
}

int setMaxDistSubTree(vector<int> &level,
                      vector<pair<int, int>> &vecmaxDist, int glade) {
    if (tree.at(glade).empty()) {
        vecmaxDist.at(glade).first = glade;
        vecmaxDist.at(glade).second = 0;
        return glade;
    }
    if (tree.at(glade).size() == 1) {
        int son = tree.at(glade).at(0);
        int result = setMaxDistSubTree(level, vecmaxDist, son);

        vecmaxDist.at(glade).first = result;
        vecmaxDist.at(glade).second = abs(level.at(glade) - level.at(result));
        return result;

    } else {
        int son1 = tree.at(glade).at(0);
        int son2 = tree.at(glade).at(1);

        int result1 = setMaxDistSubTree(level, vecmaxDist, son1);
        int result2 = setMaxDistSubTree(level, vecmaxDist, son2);

        if (level.at(result1) < level.at(result2)) {
            vecmaxDist.at(glade).first = result2;
            vecmaxDist.at(glade).second = abs(level.at(glade) - level.at
                    (result2));
            return result2;

        } else {
            vecmaxDist.at(glade).first = result1;
            vecmaxDist.at(glade).second = abs(level.at(glade) - level.at
                    (result1));
            return result1;
        }

    }
}

void setMaxDistApartTree(vector<int> &level, vector<pair<int, int>> &maxDistSub,
                         vector<pair<int, int>> &maxDistApart, vector<int> &lca,
                         int currentGlade) {
    if (currentGlade == 1) {
        maxDistApart.at(currentGlade).first = currentGlade;
        maxDistApart.at(currentGlade).second = 0;
        lca.at(currentGlade) = currentGlade;

        if (tree.at(currentGlade).size() == 1) {
            setMaxDistApartTree(level, maxDistSub, maxDistApart, lca, tree.at
                    (currentGlade).at(0));

        } else if (tree.at(currentGlade).size() == 2) {
            setMaxDistApartTree(level, maxDistSub, maxDistApart, lca, tree.at
                    (currentGlade).at(0));
            setMaxDistApartTree(level, maxDistSub, maxDistApart, lca, tree.at
                    (currentGlade).at(1));
        }
        return;
    }

    int father = parent.at(currentGlade);
    if (tree.at(father).size() == 1) {
        maxDistApart.at(currentGlade).first = maxDistApart.at(father).first;
        maxDistApart.at(currentGlade).second =
                maxDistApart.at(father).second + 1;
        lca.at(currentGlade) = lca.at(father);

    } else if (tree.at(father).size() == 2) {
        int brother;
        if (tree.at(father).at(1) == currentGlade) {
            brother = tree.at(father).at(0);
        } else {
            brother = tree.at(father).at(1);
        }

        int distSub = maxDistSub.at(brother).second + 2;
        int distApart = maxDistApart.at(father).second + 1;

        if (distApart < distSub) {
            maxDistApart.at(currentGlade).first = maxDistSub.at(brother).first;
            maxDistApart.at(currentGlade).second = distSub;
            lca.at(currentGlade) = father;

        } else {
            maxDistApart.at(currentGlade).first = maxDistApart.at(father).first;
            maxDistApart.at(currentGlade).second = distApart;
            lca.at(currentGlade) = lca.at(father);
        }
    }
    if (tree.at(currentGlade).size() == 1) {
        setMaxDistApartTree(level, maxDistSub, maxDistApart, lca, tree.at
                (currentGlade).at(0));
    } else if (tree.at(currentGlade).size() == 2) {
        setMaxDistApartTree(level, maxDistSub, maxDistApart, lca, tree.at
                (currentGlade).at(0));
        setMaxDistApartTree(level, maxDistSub, maxDistApart, lca, tree.at
                (currentGlade).at(1));
    }
}

void setMaxDist(vector<pair<int, int>> &maxDistSub,
                vector<pair<int, int>> &maxDistApart,
                vector<pair<int, int>> &maxDist,
                vector<bool> &lcaNeeded) {
    for (int i = 0; i < maxDist.size(); i++) {
        if (maxDistSub.at(i).second >= maxDistApart.at(i).second) {
            maxDist.at(i) = maxDistSub.at(i);
            lcaNeeded.at(i) = false;
        } else {
            maxDist.at(i) = maxDistApart.at(i);
            lcaNeeded.at(i) = true;
        }
    }
}

int jumpUp(
        vector<vector<int>> &jump, int glade, int distance) {

    vector<int> jumpVector = decToBin(distance);
    int size = jumpVector.size();
    for (int i = 0; i < size; i++) {
        if (jumpVector.at(i) == 1) {
            glade = jump.at(glade).at(size - 1 - i);
        }
    }
    return glade;
}

int
findDistantGlade(vector<pair<int, int>> &maxDist,
                 vector<int> &level, vector<int> &lca,
                 int glade, int distance, vector<vector<int>> &jump,
                 vector<bool> lcaNeeded) {

    int furthestGlade = maxDist.at(glade).first;
    int biggestDistance = maxDist.at(glade).second;
    int distanceToJump;
    int lcaGlade = lca.at(glade);

    if (!lcaNeeded.at(glade)) {
        distanceToJump = biggestDistance - distance;
        return jumpUp(jump, furthestGlade, distanceToJump);
    }

    if (distance <= level.at(glade) - level.at(lcaGlade)) {
        distanceToJump = distance;
        return jumpUp(jump, glade, distanceToJump);
    } else {
        distanceToJump = abs(level.at(furthestGlade) - level.at(lcaGlade)) +
                         (level.at(glade) - level.at(lcaGlade)) - distance;
        return jumpUp(jump, furthestGlade, distanceToJump);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int gladeNum, ordersNum;
    cin >> gladeNum;

    parent.at(1) = -1;
    int num1;
    int num2;

    for (int i = 1; i < gladeNum + 1; i++) {
        cin >> num1 >> num2;
        vector<int> vecSons;
        if (num1 != -1) {
            vecSons.push_back(num1);
            parent.at(num1) = i;
        }
        if (num2 != -1) {
            vecSons.push_back(num2);
            parent.at(num2) = i;
        }
        tree.insert({i, vecSons});
    }

    cin >> ordersNum;

    int maxDistance;
    int glade;
    int distance;
    int result;

    vector<pair<int, int>> maxDistSub(gladeNum + 1);
    vector<pair<int, int>> maxDistApart(gladeNum + 1);
    vector<pair<int, int>> maxDist(gladeNum + 1);
    vector<int> level(gladeNum + 1);
    vector<int> lca(gladeNum + 1, -1);
    vector<bool> lcaNeeded(gladeNum + 1, false);
    pair<int, int> res;
    vector<int> highestValue(1, 5000);

    setLevels(level, 0, 1);
    setMaxDistSubTree(level, maxDistSub, 1);
    setMaxDistApartTree(level, maxDistSub, maxDistApart, lca, 1);


    setMaxDist(maxDistSub, maxDistApart, maxDist, lcaNeeded);

    vector<vector<int>> jump(gladeNum + 1);

    for (int i = 0; i < gladeNum + 1; i++) {
        jump.at(i).resize(logMAX + 1);
    }

    for (auto &element: tree) {
        jump.at(element.first).at(0) = parent.at(element.first);
    }

    for (int i = 1; i < logMAX + 1; i++) {
        for (auto &element: tree) {
            if (jump.at(element.first).at(i - 1) == -1) {
                jump.at(element.first).at(i) = -1;
            } else {
                jump.at(element.first).at(i) = jump.at(jump.at(element.first).at
                        (i - 1)).at(i - 1);
            }
        }
    }
    for (int i = 0; i < ordersNum; i++) {
        cin >> glade >> distance;

        if (maxDist.at(glade).second >= distance) {
            cout << findDistantGlade(maxDist, level, lca, glade, distance,
                                     jump, lcaNeeded) << "\n";
        } else {
            cout << -1 << "\n";
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
