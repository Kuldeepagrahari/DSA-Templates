// ================================
// Complete Graph Algorithms Template
// ================================

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<int> adj[N];
bool visited[N];

// ================================
// Dynamic Programming Templates
// ================================

// 1. 0/1 Knapsack
// Intuition: For each item, choose to include or exclude it. Classic DP.
// Useful when item can be taken at most once.
int knapsack01(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (wt[i-1] <= w)
                dp[i][w] = max(dp[i-1][w], val[i-1] + dp[i-1][w - wt[i-1]]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    return dp[n][W];
}

// 2. Unbounded Knapsack
// Intuition: You can pick the same item again and again.
// Change direction of loops for using multiple times.
int unboundedKnapsack(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<int> dp(W+1, 0);
    for (int i = 0; i < n; i++) {
        for (int w = wt[i]; w <= W; w++) {
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }
    return dp[W];
}

// 3. Subset Sum
// Intuition: Use previous subset results to build up to target sum.
bool subsetSum(vector<int>& arr, int sum) {
    int n = arr.size();
    vector<vector<bool>> dp(n+1, vector<bool>(sum+1, false));
    for (int i = 0; i <= n; i++) dp[i][0] = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (arr[i-1] <= j)
                dp[i][j] = dp[i-1][j] || dp[i-1][j - arr[i-1]];
            else
                dp[i][j] = dp[i-1][j];
        }
    }
    return dp[n][sum];
}

// 4. Longest Common Subsequence (LCS)
// Intuition: Try all combinations of characters, and reuse previous results.
// dp[i][j] = LCS of s1[0..i-1] and s2[0..j-1]
int lcs(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[n][m];
}

// 5. Longest Increasing Subsequence (LIS)
// Intuition: Keep smallest tail values of all increasing subsequences of length i
int lis(vector<int>& nums) {
    vector<int> dp;
    for (int x : nums) {
        auto it = lower_bound(dp.begin(), dp.end(), x);
        if (it == dp.end()) dp.push_back(x);
        else *it = x;
    }
    return dp.size();
}

// 6. Edit Distance
// Intuition: Try replace/insert/delete at every mismatch
// dp[i][j] = min operations to convert s1[0..i-1] to s2[0..j-1]
int editDistance(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0) dp[i][j] = j;
            else if (j == 0) dp[i][j] = i;
            else if (s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    return dp[n][m];
}

// 7. Matrix Chain Multiplication
// Intuition: Try all partitions and take min of cost
int matrixChain(vector<int>& dims) {
    int n = dims.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + dims[i-1]*dims[k]*dims[j]);
            }
        }
    }
    return dp[1][n-1];
}

// 8. Partition Equal Subset Sum
// Intuition: Classic 1D subset sum DP
bool canPartition(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0) return false;
    int target = sum / 2;
    vector<bool> dp(target+1, false);
    dp[0] = true;
    for (int num : nums) {
        for (int i = target; i >= num; i--) {
            dp[i] = dp[i] || dp[i - num];
        }
    }
    return dp[target];
}

// 9. Coin Change (Min Coins)
// Intuition: Try all coins, minimize count to reach amount
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount+1, 1e9);
    dp[0] = 0;
    for (int coin : coins) {
        for (int x = coin; x <= amount; x++) {
            dp[x] = min(dp[x], dp[x - coin] + 1);
        }
    }
    return dp[amount] == 1e9 ? -1 : dp[amount];
}

// 10. DP on Trees
// Intuition: Postorder traversal + combine children states
// dp[node] holds result for each node depending on child
vector<int> dpTree[N];
void treeDp(int node, int parent) {
    dpTree[node] = {1};
    for (int child : adj[node]) {
        if (child == parent) continue;
        treeDp(child, node);
        // combine child dp into node dp
    }
}

// 11. Bitmask DP (e.g., Traveling Salesman Problem)
// Intuition: Each bit represents a visited state
int tsp(int mask, int pos, vector<vector<int>>& dist, vector<vector<int>>& dp) {
    int n = dist.size();
    if (mask == (1 << n) - 1) return dist[pos][0];
    if (dp[mask][pos] != -1) return dp[mask][pos];
    int ans = INT_MAX;
    for (int city = 0; city < n; city++) {
        if (!(mask & (1 << city))) {
            int newCost = dist[pos][city] + tsp(mask | (1 << city), city, dist, dp);
            ans = min(ans, newCost);
        }
    }
    return dp[mask][pos] = ans;
}

// 12. Digit DP (e.g., Count numbers with given sum of digits)
// Intuition: Use position + tight flag + sum as state
int digitDp(string& num, int pos, int sum, bool tight, vector<vector<vector<int>>>& dp) {
    if (pos == num.size()) return sum == 0;
    if (dp[pos][sum][tight] != -1) return dp[pos][sum][tight];
    int limit = tight ? num[pos] - '0' : 9, res = 0;
    for (int d = 0; d <= limit; d++) {
        if (sum - d >= 0)
            res += digitDp(num, pos+1, sum-d, tight && (d == limit), dp);
    }
    return dp[pos][sum][tight] = res;
}

// 13. DP with State Compression (e.g., for grids or transitions)
// Intuition: Compress 2D states (row, col) into 1D bitmask for memory-efficient DP
unordered_map<int, int> memo;
int compressedDp(int mask, int row, int col) {
    if (base_case) return result;
    int key = (row << 10) | (col << 5) | mask;
    if (memo.count(key)) return memo[key];
    int res = 0;
    // explore possibilities
    return memo[key] = res;
}

// 14. Game Theory DP (Grundy Numbers)
// Intuition: Use XOR properties and Grundy numbers for winning strategy
int grundy(int n, vector<int>& moves) {
    if (n == 0) return 0;
    unordered_set<int> grundies;
    for (int move : moves) {
        if (n - move >= 0)
            grundies.insert(grundy(n - move, moves));
    }
    int g = 0;
    while (grundies.count(g)) g++;
    return g;
}
