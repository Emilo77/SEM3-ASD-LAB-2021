#include <iostream>
#include <vector>

using namespace std;

long long M = 1000000000;
int P = 47;

long long M2 = 2359829439;
int P2 = 41;

void powersInit(vector<long long> &powers, vector<long long> &powers2, int n) {
    long long actual = 1;
    for (int i = 0; i < n + 2; i++) {
        powers.at(i) = actual;
        actual *= P;
        actual %= M;
    }

    actual = 1;
    for (int i = 0; i < n + 2; i++) {
        powers2.at(i) = actual;
        actual *= P2;
        actual %= M2;
    }
}

void hashInit(vector<long long> &hashSufix, vector<long long> &hashSufix2,
              int n, vector<int> &w) {

    hashSufix.at(n - 1) = w.at(n - 1);
    hashSufix2.at(n - 1) = w.at(n - 1);
    for (int i = n - 2; i >= 0; i--) {
        hashSufix.at(i) = (hashSufix.at(i + 1) * P + w.at(i)) % M;
        hashSufix2.at(i) = (hashSufix2.at(i + 1) * P2 + w.at(i)) % M2;
    }
}

long long hashCount(vector<long long> &powers, vector<long long> &hashSufix, int
i, int j) {
    long long res;
    if (j != hashSufix.size() - 1) {
        res = hashSufix.at(i) - powers.at(j - i + 1) * hashSufix.at(j + 1);
    } else {
        res = hashSufix.at(i);
    }
    if (res < 0) {
        res %= M;
        res += M;
        return res % M;

    } else {
        return res % M;
    }
}

long long hashCount2(vector<long long> &powers, vector<long long> &hashSufix,
                     int
                     i, int j) {
    long long res;
    if (j != hashSufix.size() - 1) {
        res = hashSufix[i] - powers[j - i + 1] * hashSufix[j + 1];
    } else {
        res = hashSufix[i];
    }
    if (res < 0) {
        res %= M2;
        res += M2;
        return res % M2;

    } else {
        return res % M2;
    }
}

void compareLexAndPrint(vector<long long> &powers, vector<long long> &powers2,
                        vector<int> &w, vector<long

long> &hashSufix, vector<long long> &hashSufix2, pair<int, int>
                        interval1,

                        pair<int, int> interval2) {


    if (interval1 == interval2) {
        cout << "=\n";
        return;
    }
    int low = 0;
    int high = min(interval1.second - interval1.first, interval2.second -
                                                       interval2.first);
    while (low < high) {
        int mid = (low + high) / 2;
        long long hash1 = hashCount(powers, hashSufix, interval1.first,
                                    interval1.first + mid);
        long long hash2 = hashCount(powers, hashSufix, interval2.first,
                                    interval2.first + mid);

        long long hash3 = hashCount2(powers2, hashSufix2, interval1.first,
                                     interval1.first + mid);
        long long hash4 = hashCount2(powers2, hashSufix2, interval2.first,
                                     interval2.first + mid);

        if (hash1 == hash2 && hash3 == hash4) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    int position = low;
    int lastIndex1 = interval1.second - interval1.first;
    int lastIndex2 = interval2.second - interval2.first;

    if (w.at(interval1.first + position) < w.at(interval2.first + position)) {
        cout << "<\n";
        return;
    }

    if (w.at(interval1.first + position) > w.at(interval2.first + position)) {
        cout << ">\n";
        return;
    }

    if (position == lastIndex1 && position < lastIndex2) {
        cout << "<\n";
        return;
    }

    if (position < lastIndex1 && position == lastIndex2) {
        cout << ">\n";
        return;
    }

    if (position == lastIndex1 && position == lastIndex2) {
        cout << "=\n";
        return;
    }
    cout << "WRONG";

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> w;
    char letter;

    for (int i = 0; i < n; i++) {
        cin >> letter;
        w.push_back(letter - 95);
    }

    vector<long long> powers(n + 5);
    vector<long long> powers2(n + 5);
    vector<long long> hashSufix(n);
    vector<long long> hashSufix2(n);

    powersInit(powers, powers2, n);
    hashInit(hashSufix, hashSufix2, n, w);

    pair<int, int> interval1;
    pair<int, int> interval2;

    for (int i = 0; i < m; i++) {
        cin >> interval1.first >> interval1.second;
        cin >> interval2.first >> interval2.second;

        interval1.first--;
        interval1.second--;
        interval2.first--;
        interval2.second--;

        compareLexAndPrint(powers, powers2, w, hashSufix,
                           hashSufix2, interval1,
                           interval2);
    }

    return 0;
}

//13 3
//abaababaabaab
//8 13 7 7
//6 11 4 6
//3 5 11 13
