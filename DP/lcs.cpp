#include<bits/stdc++.h>
using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.length(), m = s2.length();

    vector<vector<int>> dp(n + 1, vector<int> (m + 1, 0));
    //dp[n][m] = lcs in s1[0...n - 1] and s2[0...m - 1]

    //dp[i][j] = dp[i - 1][j] -> ith index ko assume karenge ki vo move kiya h isliye hamne i - 1 th row me gye, ye mante hue ki yahi se move karke yaha pahucha hoga, jth col me hi kyuki hum isko maan rahe h ki dusre ka index nhi move hua h
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(s1[i - 1] == s2[j - 1]) 
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max (0 + dp[i - 1][j], 0 + dp[i][j - 1]);
            }
        }
    }
    int lcsLen= dp[n][m];

    // Printing LCS
    int i = n - 1, j = m - 1;
    string lcs = "";
    
    // peeche wale ko dekh kar hamne dp table fill kiya tha, to peeche wale ko hi dekh kar compare karenge aur accordingly pointers move karenge -> jisko move krne se jada badi lcs milni hogi
    while(i >= 0 && j >= 0) 
    {
        if(s1[i] == s2[j]) 
        {
            lcs = s1[i] + lcs;
            i--;
            j--;
        }
        else 
        {
            if(dp[i][j + 1] > dp[i + 1][j]) i--;
            else j--;
        }  
    }
    cout << lcs << endl;
}