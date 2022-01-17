#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    int a[n];

    vector<long long> et;
    for (int i = 0; i < n; i++) {
        et.push_back(0);
    }

    long long powerOf2 = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[j];
            if (j >= n / 2) {
                et.at(a[j] - 1) += powerOf2;
            }
        }
        powerOf2 *= 2;
    }
    sort(et.begin(), et.end());

    for (int i = 0; i < n - 1; i++) {
        if (et.at(i) == et.at(i + 1)) {
            cout << "NIE";
            return 0;
        }
    }
    cout << "TAK";
    return 0;
}
