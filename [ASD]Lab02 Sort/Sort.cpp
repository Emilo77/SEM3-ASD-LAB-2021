#include <iostream>

using namespace std;

int lslArray[1000][1000];
int lsrArray[1000][1000];


int LSR(const int arr[], int i, int j);

int LSL(const int arr[], int i, int j) {
    if (j == i + 1) {
        if (arr[i] < arr[i + 1])
            return 1;
        else return 0;
    }

    int &w = lslArray[i][j];
    if (w != -1) {
        return w % 1000000000;
    }
    w = 0;

    if (arr[i] < arr[i + 1] && arr[i] < arr[j]) {
        w += (LSL(arr, i + 1, j) + LSR(arr, i + 1, j));

    } else if (arr[i] < arr[i + 1]) {
        w += LSL(arr, i + 1, j);

    } else if (arr[i] < arr[j]) {
        w += LSR(arr, i + 1, j);
    }
    w %= 1000000000;
    lslArray[i][j] = w;
    return w;
}

int LSR(const int arr[], int i, int j) {
    if (j == i + 1) {
        if (arr[i] < arr[i + 1])
            return 1;
        else return 0;
    }

    int &w = lsrArray[i][j];
    if (w != -1) {
        return w % 1000000000;
    }
    w = 0;

    if (arr[j - 1] < arr[j] && arr[i] < arr[j]) {
        w += (LSL(arr, i, j - 1) + LSR(arr, i, j - 1));

    } else if (arr[j - 1] < arr[j]) {
        w += LSR(arr, i, j - 1);

    } else if (arr[i] < arr[j]) {
        w += LSL(arr, i, j - 1);
    }
    w %= 1000000000;
    lsrArray[i][j] = w;
    return w;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    unsigned long int n;
    cin >> n;
    int arr[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            lslArray[i][j] = -1;
            lsrArray[i][j] = -1;
        }
    }

    if (n == 1) {
        cout << 1;
    } else {
        cout << (LSL(arr, 0, n - 1) + LSR(arr, 0, n - 1)) % 1000000000;
    }
    return 0;
}
