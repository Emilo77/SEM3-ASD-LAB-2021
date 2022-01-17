#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

void change(vector<set<int>> &next, vector<int> &deg, pair<int, int>
deleted,priority_queue<pair<int, int>, std::vector<pair<int, int>>,
        std::greater<> > &que, vector<int> &peopleNeeded) {

    deg.at(deleted.second) = -1;
    for(int element : next.at(deleted.second)) {
        if(deg.at(element) == 1) {
            que.push({peopleNeeded.at(element), element});
            deg.at(element) = -1;
        }
        else if(deg.at(element) > 0) {
            deg.at(element)--;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> peopleNeeded;
    peopleNeeded.push_back(-1);
    int temp;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        peopleNeeded.push_back(temp);
    }

    vector<int> deg(n + 2, 0);
    deg.at(0) = -1;

    vector<set < int>> next;
    next.resize(n + 2);//albo + 2
    int num1, num2;
    for (int i = 0; i < m; i++) {
        cin >> num1 >> num2;
        if (next.at(num2).count(num1) == 0) {
            next.at(num2).insert(num1);
            deg.at(num1)++;
        }
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<> > minQue;

    for(int i = 1; i < n + 1; i++) {
        if(deg.at(i) == 0) {
            minQue.push({peopleNeeded.at(i), i});
            deg.at(i) = -1;
        }
    }


    int found  = 0;
    int min = 0;

    while(found < k) {

        auto actualMin = minQue.top();
        if(min < actualMin.first) {
            min = actualMin.first;
        }
        minQue.pop();
        found++;
        change(next, deg, actualMin, minQue, peopleNeeded);
    }

    cout << min << endl;

}
//5 3 3
//10
//500
//150
//200
//100
//1 2
//1 3
//4 5