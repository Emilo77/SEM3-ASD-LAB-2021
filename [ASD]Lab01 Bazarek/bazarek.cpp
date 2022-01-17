#include <iostream>
#include <climits>
#include <vector>


using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int prodAmount;
    cin >> prodAmount;

    int prodPrices[prodAmount];

    for(int i = 0; i < prodAmount; i++) {
        cin >> prodPrices[i];
    }

    int daysNumber;
    cin >> daysNumber;
    int numOfProductsToBuy[daysNumber];

    for(int i = 0; i < daysNumber; i++) {
        cin >> numOfProductsToBuy[i];
    }



    long long unsigned int sum[prodAmount + 1];
    sum[0] = 0;
    long long unsigned int currentSum = 0;
    int maxEven[prodAmount + 1];
    int maxOdd[prodAmount + 1];
    int ind = 0;
    int currentMaxEven = INT_MIN;
    int currentMaxOdd = INT_MIN;

    while(ind < prodAmount) {
        currentSum += prodPrices[prodAmount - ind - 1];
        sum[ind + 1] = currentSum;

        if(prodPrices[ind] % 2 == 0) {
            currentMaxEven = prodPrices[ind];
        }
        else {
            currentMaxOdd = prodPrices[ind];
        }
        maxEven[prodAmount - ind - 1] = currentMaxEven;
        maxOdd[prodAmount - ind - 1] = currentMaxOdd;
        ind++;
    }
    maxEven[prodAmount] = INT_MIN;
    maxOdd[prodAmount] = INT_MIN;

    int minEven[prodAmount + 1];
    int minOdd[prodAmount + 1];
    int currentMinEven = INT_MAX;
    int currentMinOdd = INT_MAX;

    ind = 0;
    minEven[0] = INT_MAX;
    minOdd[0] = INT_MAX;

    while(ind < prodAmount) {
        if(prodPrices[prodAmount - ind - 1] % 2 == 0) {
            currentMinEven = prodPrices[prodAmount - ind - 1];
        }
        else {
            currentMinOdd = prodPrices[prodAmount - ind - 1];
        }
        minEven[ind + 1] = currentMinEven;
        minOdd[ind + 1] =  currentMinOdd;
        ind++;
    }

    for(int i = 0; i < daysNumber; i++) {
        if(sum[numOfProductsToBuy[i]] % 2 == 1) {
            cout << sum[numOfProductsToBuy[i]] << "\n";
        }
        else {
            unsigned int maxEvenValue  = maxEven[numOfProductsToBuy[i]];
            unsigned int maxOddValue = maxOdd[numOfProductsToBuy[i]];
            unsigned int minEvenValue  = minEven[numOfProductsToBuy[i]];
            unsigned int minOddValue = minOdd[numOfProductsToBuy[i]];

            int unsigned long long change1 = minEven[numOfProductsToBuy[i]] -
                                             maxOdd[numOfProductsToBuy[i]];
            int unsigned long long change2 = minOdd[numOfProductsToBuy[i]] -
                                             maxEven[numOfProductsToBuy[i]];

            if((maxEvenValue == INT_MIN && minEvenValue == INT_MAX) ||
               (maxEvenValue == INT_MIN && maxOddValue == INT_MIN)||
               (minOddValue == INT_MAX  && maxOddValue == INT_MIN) ||
               (minOddValue == INT_MAX && minEvenValue == INT_MAX)) {
                cout << -1 << "\n";
            }
            else if((maxEvenValue == INT_MIN || minOddValue == INT_MAX)) {
                cout << sum[numOfProductsToBuy[i]] - change1 << "\n";
            }
            else if(maxOddValue == INT_MIN || minEvenValue == INT_MAX) {
                cout << sum[numOfProductsToBuy[i]] - change2 << "\n";
            }
            else if(change1 > change2) {
                cout << sum[numOfProductsToBuy[i]] - change2 << "\n";
            }
            else {
                cout << sum[numOfProductsToBuy[i]] - change1 << "\n";
            }
        }
    }
}

//4
//1 2 3 4
//3
//2
//3
//4
