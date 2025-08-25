#include<bits/stdc++.h>
using namespace std;
const int Inf = 1e9;
int main() {
    int n, sum;
    cin >> n >> sum;
    vector<int> coins(n);
    for(int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    // ---------------------------------------------------------------------------------------------------------------------
    // tabulation : dp[sum][coin] = min no. of coins req to make sum = sum using denominations of coin from 0 to coin indices -> coins[0...coin]
    // vector<vector<int>> dp(sum + 1, vector<int> (n + 1, Inf));
    // // Base Case: if sum == 0, then no more coin is required so return 0
    // for(int i = 1; i <= n; i++) dp[0][i] = 0;
    
    // for(int i = 1; i <= sum; i++) {
    //     for(int coin = 1; coin <= n; coin ++) {
    //         int reducedSum = i - coins[coin - 1];
    //         if(reducedSum >= 0) {
    //             dp[i][coin] = min (dp[i][coin], 1 + dp[reducedSum][coin]); // we will check for same coin, as i can take as much coin as i want of same value
    //         }
    //         dp[i][coin] = min (dp[i][coin], 0 + dp[i][coin - 1]);
    //     }
    // }
    // for(int i = 0; i <= sum; i++) {
    //     for(int coin = 0; coin <= n; coin ++) {
    //        cout << dp[i][coin] << " ";
    //     }
    //     cout << endl;
    // }
    //-------------------------------------------------------------------------------------------------------------------------  
    // Space Optimization : dp[sum] = min no. of coins required to make sum = sum, no matter what denomination of coins you used but check for best denomination which can lead to minimum no. of coins for sum = sum
    // Approach : We will run nested loops and check with all denominations and track min no. of coins required to make sum = sum and store into dp[sum], next time when we will be require to use this value -> that will be the min of all denominations, so storing with index is not require
  
    // we will initially assume that sum can be made with Inf no. of coins
    vector<int> dp(sum + 1, Inf);

    // Base case: if sum == 0, we will req no coin
    dp[0] = 0;

    for(int i = 1; i <= sum; i++) {
        for(int coin = 1; coin <= n; coin ++) {
            int reducedSum = i - coins[coin - 1];
            if(reducedSum >= 0) {
                dp[i] = min (dp[i], 1 + dp[reducedSum]);
            }
        }
    }
    for(int i = 0; i <= sum; i++) cout << dp[i] << " ";
    cout << endl;
    cout << dp[sum] << endl;

}