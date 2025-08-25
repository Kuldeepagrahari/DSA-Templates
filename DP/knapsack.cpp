#include<bits/stdc++.h>
using namespace std;

int K(vector<int>& wt, vector<int>& val, vector<vector<int>>& dp, int ind, int W) {
    if(ind == wt.size()) return 0;
    if(dp[W][ind] != -1) return dp[W][ind];
    int take = 0, skip = 0;
    int reducedW = W - wt[ind];
    if(reducedW >= 0) {
        take = val[ind] + K(wt, val, dp, ind + 1, reducedW);
    }
    skip = 0 + K(wt, val, dp, ind + 1, W);
    return dp[W][ind] = max(take, skip);
}
int main() {
    int n, W;
    cin >> n >> W;

    vector<int> wt(n);
    vector<int> val(n);

    for(int i = 0; i < n; i++) {
        cin >> wt[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> val[i];
    }
    
    // dp[i][j] = max total value can be gathered after handling total i weight with any no. of bags and also choosing from [0.....j] subarray of bags, it will have max possible upto index j
    vector<vector<int>> dp(W + 1, vector<int> (n + 1, 0));
    
   
    for (int weight = 1; weight <= W; weight ++) {
        for (int ind = 1; ind <= n; ind ++) {
            int take = 0, skip = 0;
            int reducedW = weight - wt[ind - 1];
            if(reducedW >= 0) {
                take = val[ind - 1] + dp[reducedW][ind - 1]; // you can blindly believe that (ind - 1)th column have the max possible total value upto ind - 1 for each W
            }
            skip = 0 + dp[weight][ind - 1];
            dp[weight][ind] = max (take, skip);
        }
    }
    int ans = dp[W][n];
    cout << ans << endl;


    
}