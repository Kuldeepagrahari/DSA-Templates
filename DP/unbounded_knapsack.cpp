#include<bits/stdc++.h>
using namespace std;
// Unbounded: Bag with same weight and val can be present multiple times
int K(vector<int>& wt, vector<int>& val, vector<vector<int>>& dp, int ind, int W) {
    if(ind == wt.size()) return 0;
    if(dp[W][ind] != -1) return dp[W][ind];
    int take = 0, skip = 0;
    int reducedW = W - wt[ind];
    if(reducedW >= 0) {
        take = val[ind] + K(wt, val, dp, ind, reducedW);
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
    // vector<vector<int>> dp(W + 1, vector<int> (n + 1, 0));
    
   
    // for (int weight = 1; weight <= W; weight ++) {
    //     for (int ind = 1; ind <= n; ind ++) {
    //         int take = 0, skip = 0;
    //         int reducedW = weight - wt[ind - 1];
    //         if(reducedW >= 0) {
    //             take = val[ind - 1] + dp[reducedW][ind]; // you can blindly believe that (ind)th column have the max possible total value upto ind for each W
    //         }
    //         skip = 0 + dp[weight][ind - 1];
    //         dp[weight][ind] = max (take, skip);
    //     }
    // }

    // Space Optimization
    // dp[wt] = max possible total val you can achieve after holding weight = wt, it will be dependent on dp[wt - w[ind]] and dp[wt] matlab agar hum cur bag ko le to iske liye bina weight ke liye max tot val kya thi + cur bag lene ke ki val ya fir agar hum cur ko na le to isi weight ke liye abhi tak total max value jo tha

    // hum 2-d ko 1-d isiliye bana paye h kyuki hame jo prev row ki jarurat pad rahi usme uska max value ki h jarurat padegi hamesha, to index wise store krne ki jarurat nhi h, hum directly wt se hi access karenge aur jo cur row ki jarurat pad rahi h uski bhi abhi tak ki max value hi chahiye to uske liye bhi index wise store nhi krna pad raha h
    // to 2 loop kyu? -> isliye kyuki max value tabhi pta chalegi har wt ke liye jab sab bago se try karle -> to sabse try krte krte abhi tak ka max store krte jaenge 
    vector<int> dp(W + 1, 0);
     for (int weight = 1; weight <= W; weight ++) {
        for (int ind = 1; ind <= n; ind ++) {
            int take = 0, skip = 0;
            int reducedW = weight - wt[ind - 1];
            if(reducedW >= 0) {
                take = val[ind - 1] + dp[reducedW]; // you can blindly believe that (ind)th column have the max possible total value upto ind for each W
            }
            skip = 0 + dp[weight];
            dp[weight] = max (take, skip);
        }
    }
    int ans = dp[W];
    // int ans = K(wt, val, dp, 0, W);
    cout << ans << endl;


    
}