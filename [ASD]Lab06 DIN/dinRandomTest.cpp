#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include "assert.h"


using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::swap;
using std::vector;


void invertDNA(string &dna, int start, int end) {
    int interval = end - start + 1;

    string tempString = dna.substr(start, interval);
    std::reverse(tempString.begin(), tempString.end());

    dna.erase(start, interval);
    dna.insert(start, tempString);
}

void deleteMoveDNA(string &dna, int start, int end, int newInd) {
    if (start == newInd) {
        return;
    }

    int interval = end - start + 1;
    if (interval == dna.size()) {
        return;
    }
    string tempString = dna.substr(start, interval);
    dna.erase(start, interval);
    dna.insert(newInd, tempString);
}

//do zmiany, potrzebne do tego drzewo
int findBiggestSeq(string &dna, int start, int end) {
    int max = 1;
    int actual = 1;
    char actualChar = 'X';
    for (int ind = start; ind <= end; ind++) {
        if (dna.at(ind) != actualChar) {
            actual = 1;
            actualChar = dna.at(ind);
        } else {
            actual++;
            if (actual > max) {
                max = actual;
            }
        }
    }
    return max;
}

void test(int n, int m) {
    string dna;
    int randomLetter;
    int randomInstr;
    for (int i = 0; i < n; i++) {
        randomLetter = rand() % 4;
        if (randomLetter == 0) {
            dna.append("C");
        } else if (randomLetter == 1) {
            dna.append("A");
        } else if (randomLetter == 2) {
            dna.append("T");
        } else dna.append("G");
    }
    int randomStart;
    int randomEnd;
    int randomNewInd;
    char instructions[m];

    for (int i = 0; i < m; i++) {
        randomInstr = rand() % 3;
        if (randomInstr == 0) {
            instructions[i] = 'P';
        } else if (randomInstr == 1) {
            instructions[i] = 'O';
        } else {
            instructions[i] = 'N';
        }
    }

    cout << n << " " << m << "\n";
    cout << dna << "\n";
    for (int i = 0; i < m; i++) {
        randomStart = (rand() % n) + 1;
        randomEnd = rand() % (n - randomStart + 1) + randomStart;
        randomNewInd = rand() % (n - (randomEnd - randomStart)) + 1;

        assert(randomStart <= randomEnd);
        assert(randomNewInd <= n - randomEnd + randomStart);

        if (instructions[i] == 'P') {
            cout << instructions[i] << " " << randomStart << " " << randomEnd
                 << " " <<
                 randomNewInd << "\n";
        } else {
            cout << instructions[i] << " " << randomStart << " " << randomEnd
                 << "\n";
        }
    }
}


int main() {

    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bool TESTING = true;
    int DNASIZE = 30;
    int INSTRUCTIONSNUMBER = 22;
    int TESTNUM = 5;

    bool DEBUG = false;

    if (TESTING) {
        for (int i = 0; i < TESTNUM; i++) {
            cout << "\n";
            test(DNASIZE, INSTRUCTIONSNUMBER);
            cout << "\n";
        }
    } else {
        int n;
        int m;
        string temp;


        cin >> n >> m;
        cin >> temp;
        string dna = "X";
        dna.append(temp);


        int startInd;
        int endInd;
        int newInd = 0;
        char instr;

        for (int i = 0; i < m; i++) {
            cin >> instr;

            if (instr == 'O') {
                cin >> startInd >> endInd;
                if (DEBUG) {
                    cout << 'O' << " " << startInd << " " << endInd << "\n";
                }
                invertDNA(dna, startInd, endInd);
                //updateTree(tree, start, end);

            } else if (instr == 'P') {
                cin >> startInd >> endInd >> newInd;
                if (DEBUG) {
                    cout << 'P' << " " << startInd << " " << endInd << " "
                         << newInd << "\n";
                }
                deleteMoveDNA(dna, startInd, endInd, newInd);

            } else {
                cin >> startInd >> endInd;
                if (DEBUG) {
                    cout << 'N' << " " << startInd << " " << endInd << "\n";
                }
                cout << findBiggestSeq(dna, startInd, endInd) << "\n";
            }
            if (DEBUG) {
                for (int j = 1; j < dna.length(); j++) {
                    cout << dna[j];
                }
                cout << "\n";
            }
        }
    }
}