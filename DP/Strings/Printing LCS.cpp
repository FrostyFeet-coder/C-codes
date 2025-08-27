#include <bits/stdc++.h>
using namespace std;

string longestCommonSubsequence(string text1, string text2) {
    int n = text1.size();
    int m = text2.size();

    // dp[i][j] ka matlab = LCS length of text1 ke first i characters aur text2 ke first j characters
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Base case: agar koi string empty hai toh LCS = 0
    for(int i = 0; i <= n; i++) dp[i][0] = 0;  // text2 empty hai
    for(int j = 0; j <= m; j++) dp[0][j] = 0;  // text1 empty hai

    // DP table fill karna
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(text1[i - 1] == text2[j - 1]){
                // Agar characters match huye -> diagonal se value + 1 lenge
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                // Agar characters match nahi huye -> top ya left se max lenge
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // DP table print karna debugging ke liye (optional)
    cout << "DP Table:" << endl;
    for(int i = 0 ; i <= n ; i++){
        for(int j = 0 ; j <= m ; j++){
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    // Ab LCS ko build karenge using backtracking
    int i = n, j = m;
    string lcs = "";

    while(i > 0 && j > 0){
        if(text1[i-1] == text2[j-1]){
            // Agar character match kar gya -> yeh LCS ka part hoga
            lcs += text1[i-1];  
            i--; j--;  // diagonal move karenge
        } else if(dp[i-1][j] > dp[i][j-1]){
            // Agar upar wali value badi hai -> upar move karenge
            i--;
        } else {
            // Agar left wali value badi hai -> left move karenge
            j--;
        }
    }

    // Humne LCS ko reverse order me build kiya tha, isliye reverse karna hoga
    reverse(lcs.begin(), lcs.end());

    return lcs; // final LCS return karenge
}

int main(){
    string s1 = "abc";
    string s2 = "abde";

    cout << "Longest Common Subsequence: " << longestCommonSubsequence(s1, s2);

    return 0;
}
