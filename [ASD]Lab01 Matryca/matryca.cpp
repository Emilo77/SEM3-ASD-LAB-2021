#include <iostream>

using namespace std;

bool onlyOneLetter(string &s) {
    unsigned long sLength = s.length();
    char start;
    bool found = false;
    for (int i = 0; i < sLength; i++) {
        if (s[i] != '*') {
            start = s[i];
            found = true;
            break;
        }
    }
    if (!found)
        return true;
    for (int i = 1; i < sLength; i++) {
        if (s[i] != start && s[i] != '*') {
            return false;
        }
    }
    return true;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    if (onlyOneLetter(s)) {
        cout << "1";
        return 0;
    }

    int l = 1000000;
    char start = '\0';
    int indHelper = -1;
    unsigned long sLength = s.length();

    for (int i = 0; i < sLength; i++) {

    }
    for (int i = 0; i < sLength; i++) {
        if (s[i] != '*') {
            if (start != '\0' && s[i] != start) {
                int k;
                if (indHelper == -1) {
                    k = i + 1;
                } else {
                    k = i + 1 - indHelper;
                }
                if (l > k) {
                    l = k;
                }
            }
            start = s[i];
            indHelper = i;
        }
    }
    cout << sLength - l + 2;
    return 0;

}
