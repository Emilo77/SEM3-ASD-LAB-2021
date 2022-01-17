#include <iostream>
#include <vector>

using namespace std;

int pow2(int n) {
    int res = 1;
    while (res < n) {
        res *= 2;
    }
    return res;
}

void insert(pair<int, int> newinterval, int colour, vector<int> &colourArr, int
node, pair<int, int> interval, vector<int> &whiteSum) {
    if (newinterval.first > interval.second || newinterval.second < interval
            .first) {
        return;
    } else if (newinterval.first <= interval.first && newinterval.second >=
                                                      interval.second) {
        colourArr[node] = colour;

        if (colour == 1) {
            whiteSum[node] = 0;
        } else {
            whiteSum[node] = interval.second - interval.first + 1;
        }
    } else {
        if (colourArr[node] != 2) {
            colourArr[2 * node] = colourArr[node];
            colourArr[2 * node + 1] = colourArr[node];

            if (colourArr[node] == 0) {
                whiteSum[2 * node] = (interval.second - interval.first + 1) / 2;
                whiteSum[2 * node + 1] = (interval.second - interval.first + 1)
                                         / 2;
            } else {
                whiteSum[2 * node] = 0;
                whiteSum[2 * node + 1] = 0;
            }

        }
        pair<int, int> firstHalf;
        firstHalf.first = interval.first;
        firstHalf.second = (interval.first + interval.second) / 2;
        pair<int, int> secondHalf;
        secondHalf.first = (interval.first + interval.second) / 2 + 1;
        secondHalf.second = interval.second;

        insert(newinterval, colour, colourArr, 2 * node, firstHalf,
               whiteSum);
        insert(newinterval, colour, colourArr, 2 * node + 1, secondHalf,
               whiteSum);

        colourArr[node] = 2;
        whiteSum[node] = whiteSum[2 * node] + whiteSum[2 * node + 1];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    int m;

    cin >> n;
    cin >> m;

    int leavesNum = pow2(n);
    int nodesNum = 2 * leavesNum;

    vector<int> colour;
    colour.reserve(nodesNum);

    vector<int> whiteSum;
    whiteSum.reserve(2 * leavesNum);

    for (int i = 0; i < nodesNum; i++) {
        colour.push_back(1);
        whiteSum.push_back(0);
    }
    vector<int> res;
    char newColour;

    for (int ind = 0; ind < m; ind++) {

        pair<int, int> newInterval;
        cin >> newInterval.first;
        cin >> newInterval.second;
        cin >> newColour;

        newInterval.first--;
        newInterval.second--;
        pair<int, int> startingInterval = {0, leavesNum - 1};

        insert(newInterval, newColour == 'C' ? 1 : 0, colour, 1,
               startingInterval,
               whiteSum);

        res.push_back(whiteSum[1]);
    }


    for (int ind = 0; ind < m; ind++) {
        cout << res[ind] << endl;
    }
//12
//4
//1 5 C
//2 10 B
//4 6 B
//4 7 C

//0 biały
//1 czarny
//2 szary

}
