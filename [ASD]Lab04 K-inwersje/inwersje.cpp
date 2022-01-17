#include <iostream>

using std::cin;
using std::cout;

const long M = 1000000000;

int pow2(int n) {
    int res = 1;
    while (res < n) {
        res *= 2;
    }
    return res;
}

long sum(int leafNumber, int leafAmount, const long tree[]) {
    int v = leafAmount + leafNumber;
    long sum = 0;
    while (v > 1) {
        if (v % 2 == 0) {
            sum = (sum + tree[v + 1]) % M;
        }
        v /= 2;
    }
    return sum;
}

void treeChange(int leafNumber, int leafAmount, long value, long tree[]) {
    int v = leafAmount + leafNumber;
    while (v > 1) {
        tree[v] = (tree[v] + value) % M;
        v /= 2;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i]--;
    }
    if (k == 1) {
        cout << n;
        return 0;
    }

    int leavesNum = pow2(n);
    int nodesNum = 2 * leavesNum;

    long tree[nodesNum];
    for (int i = 0; i < nodesNum; i++) {
        tree[i] = 0;
    }

    long helpingArr[n];
    long helpingArr2[n];

    for (int i = 0; i < n; i++) {
        helpingArr[i] = 1;
        helpingArr2[i] = 1;
    }

    for (int i = 1; i < k; i++) {
        for (int j = 0; j < n; j++) {
            if (i % 2) {
                helpingArr2[arr[j]] = sum(arr[j], leavesNum, tree);
                treeChange(arr[j], leavesNum, helpingArr[arr[j]], tree);
            } else {
                helpingArr[arr[j]] = sum(arr[j], leavesNum, tree);
                treeChange(arr[j], leavesNum, helpingArr2[arr[j]], tree);
            }
        }
        for (int j = 0; j < nodesNum; j++) {
            tree[j] = 0;
        }
    }
    long long sum = 0;

    if (k % 2 == 0) {
        for (int i = 0; i < n; i++) {
            sum = (sum + helpingArr2[i]) % M;
        }
    } else {
        for (int i = 0; i < n; i++) {
            sum = (sum + helpingArr[i]) % M;
        }
    }
    cout << sum;
    return 0;
}
