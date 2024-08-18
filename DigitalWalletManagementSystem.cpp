#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int main() {
    int n;
    cin >> n;
    //1d array-->read and store userid and balances
    int userid[n], balances[n];
    for (int i = 0; i < n; i++) {
        cin >> userid[i] >> balances[i];
    }
    int t;
    cin >> t;
    //2d array-->read and store transactions
    int transactions[t][3];
    for (int i = 0; i < t; i++) {
        cin >> transactions[i][0] >> transactions[i][1] >> transactions[i][2];
    }
    //1d array-->store transaction results (success or failure)
    string results[t];
    //linear search-->to find the user
    auto finduser = [&](int userID) {
        for (int i = 0; i < n; i++) {
            if (userid[i] == userID) {
                return i;
            }
        }
        return -1;
    };
    //conditional and update-->check, remove, add, success or failure
    auto dotransaction = [&]() {
        for (int i = 0; i < t; i++) {
            int fromid = transactions[i][0];
            int toid = transactions[i][1];
            int amount = transactions[i][2];
            int fromIndex = finduser(fromid);
            int toIndex = finduser(toid);
            if (balances[fromIndex] >= amount) {
                balances[fromIndex] -= amount;
                balances[toIndex] += amount;
                results[i] = "Success";
            } else {
                results[i] = "Failure";
            }
        }
    };
    //bubble sort-->sort user balances in ascending order
    auto sortUsers = [&]() {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (balances[j] > balances[j + 1] || 
                    (balances[j] == balances[j + 1] && userid[j] > userid[j + 1])) {
                    int tempBalance = balances[j];
                    balances[j] = balances[j + 1];
                    balances[j + 1] = tempBalance;
                    int tempUserID = userid[j];
                    userid[j] = userid[j + 1];
                    userid[j + 1] = tempUserID;
                }
            }
        }
    };
    dotransaction();
    sortUsers();
    for (int i = 0; i < t; i++) {
        cout << results[i] << endl;
    }
    cout<<endl;
    for (int i = 0; i < n; i++) {
        cout << userid[i] << " " << balances[i] << endl;
    }
    return 0;
}