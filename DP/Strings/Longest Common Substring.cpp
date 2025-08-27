#include <bits/stdc++.h>
using namespace std;

// Function to find the longest common substring between two strings
// Time Complexity: O(n * m)
// Space Complexity: O(n * m)
string longestCommonSubstring(string text1, string text2) {
    int n = text1.size();
    int m = text2.size();

    // dp[i][j] yeh batata hai ki text1 ke i-1 index tak aur text2 ke j-1 index tak
    // longest common substring ki length kya hai jo dono me end ho rahi hai
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    int maxLen = 0;   // ab tak ka sabse bada substring ka length
    int endIndex = 0; // text1 me substring kaha end ho raha hai, uska index

    // DP table fill kar rahe hain
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            // agar dono string ke current character same hain
            if(text1[i - 1] == text2[j - 1]){
                // previous diagonal value se 1 add kar do
                dp[i][j] = 1 + dp[i - 1][j - 1];

                // agar naya length max se bada hai toh update karo
                if(dp[i][j] > maxLen){
                    maxLen = dp[i][j];
                    endIndex = i - 1; // substring ka end index store karo
                }
            } else {
                dp[i][j] = 0; // agar match nahi hua toh substring break ho gaya
            }
        }
    }

    // ab substring extract karna hai, jo endIndex - maxLen + 1 se leke endIndex tak hai
    string lcs = text1.substr(endIndex - maxLen + 1, maxLen);

    return lcs;
}

int main(){
    string s1 = "abcdf";
    string s2 = "abedf";

    // longestCommonSubstring function call kar rahe hain aur result print kar rahe hain
    cout << "Longest Common Substring: " << longestCommonSubstring(s1, s2) << endl;

    return 0;
}


// =================== Tabulation Approach ===================

#include <bits/stdc++.h>
using namespace std;

// Longest Common Substring using 2D DP (Tabulation)
// Time Complexity: O(n * m)
// Space Complexity: O(n * m)
int longestCommonSubstringTabulation(string text1, string text2) {
    int n = text1.size();
    int m = text2.size();

    // dp[i][j] yeh batata hai ki text1 ke i-1 index tak aur text2 ke j-1 index tak
    // longest common substring ki length kya hai jo dono me end ho rahi hai
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    int maxLen = 0; // ab tak ka max substring length

    // DP table fill kar rahe hain
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            // agar character match ho gaya toh diagonal se 1 add karo
            if(text1[i - 1] == text2[j - 1]){
                dp[i][j] = 1 + dp[i - 1][j - 1]; // diagonal se length badhao
                maxLen = max(maxLen, dp[i][j]);  // max length update karo
            } else {
                dp[i][j] = 0; // match nahi hua toh substring break ho gaya
            }
        }
    }

    return maxLen; // sirf length return kar rahe hain
}

int main(){
    string s1 = "abcdf";
    string s2 = "abedf";

    // longestCommonSubstringTabulation function call kar rahe hain aur result print kar rahe hain
    cout << "Longest Common Substring Length (Tabulation): " 
         << longestCommonSubstringTabulation(s1, s2) << endl;

    return 0;
}


// =================== Space Optimized Approach ===================

#include <bits/stdc++.h>
using namespace std;

// Longest Common Substring using Space Optimization
// Time Complexity: O(n * m)
// Space Complexity: O(m)
int longestCommonSubstringOptimized(string text1, string text2) {
    int n = text1.size();
    int m = text2.size();

    // Sirf do rows ka use kar rahe hain, ek previous aur ek current
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    int maxLen = 0; // ab tak ka max substring length

    // DP table fill kar rahe hain, lekin sirf 1D arrays ka use karke
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            // agar character match ho gaya toh previous row ke diagonal se 1 add karo
            if(text1[i - 1] == text2[j - 1]){
                curr[j] = 1 + prev[j - 1];
                maxLen = max(maxLen, curr[j]); // max length update karo
            } else {
                curr[j] = 0; // match nahi hua toh substring break ho gaya
            }
        }
        prev = curr; // current row ko previous row bana do next iteration ke liye
    }

    return maxLen; // sirf length return kar rahe hain
}

int main(){
    string s1 = "abcdf";
    string s2 = "abedf";

    // longestCommonSubstringOptimized function call kar rahe hain aur result print kar rahe hain
    cout << "Longest Common Substring Length (Optimized): " 
         << longestCommonSubstringOptimized(s1, s2) << endl;

    return 0;
}
