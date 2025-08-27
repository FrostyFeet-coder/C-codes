
/*
    Problem: 583. Delete Operation for Two Strings
    Approach: Longest Common Subsequence (LCS) ka use karke minimum delete operations nikalna hai.

    Time Complexity (TC): O(n*m)
    Space Complexity (SC): O(m) -- kyunki hum sirf 2 rows use kar rahe hain (prev & curr)

    Step by Step Explanation (Hinglish Comments):

    1. lcs() function:
        - Ye function do strings ka LCS length nikalta hai.
        - Hum 2 vectors (prev, curr) use kar rahe hain space optimize karne ke liye.
        - Nested loops se har character compare karte hain.
        - Agar match hota hai, toh 1 + prev diagonal value lete hain.
        - Agar nahi match hota, toh max lete hain (left ya upar se).
        - Last mein prev[m] return karte hain, jo LCS length hai.

    2. minDistance() function:
        - Pehle dono strings ki length nikalte hain.
        - lcs() se LCS length nikalte hain.
        - Minimum delete operations = (n - LCS) + (m - LCS) = n + m - 2*LCS
        - Ye formula isliye kaam karta hai kyunki LCS ko chhodke baaki sab delete karna padega.

    Example:
        word1 = "sea", word2 = "eat"
        LCS = "ea" (length 2)
        Min deletions = 3 + 3 - 2*2 = 2

    Note:
        - Ye approach tabhi kaam karegi jab sirf delete operation allowed ho.
        - Agar insert/replace allowed hota toh DP thoda alag hota.
*/

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    // Function to find the length of the Longest Common Subsequence (LCS) between two strings
    int lcs(string s1, string s2){
        int n = s1.size(), m = s2.size(); // n = length of s1, m = length of s2

        // We use two 1D arrays to save space (instead of a 2D DP table)
        vector<int> prev(m+1, 0), curr(m+1, 0);

        // Loop through each character of s1
        for(int i=1; i<=n; i++){
            // Loop through each character of s2
            for(int j=1; j<=m; j++){
                // If current characters match, add 1 to the result from previous indices
                if(s1[i-1] == s2[j-1]){
                    curr[j] = 1 + prev[j-1];
                }
                // If not matching, take the maximum value by either skipping a char from s1 or s2
                else{
                    curr[j] = max(prev[j], curr[j-1]);
                }
            }
            // Move current row to previous for next iteration
            prev = curr;
        }
        // The last value in prev contains the length of LCS
        return prev[m];
    }

    // Function to find the minimum number of deletions to make two strings equal
    int minDistance(string word1, string word2) {
        int n = word1.length(); // Length of first word
        int m = word2.length(); // Length of second word

        int ans = lcs(word1, word2); // Find LCS length

        // Minimum deletions = total chars - 2 * LCS length
        // (delete non-LCS chars from both strings)
        return n + m - 2 * ans;
    }
};