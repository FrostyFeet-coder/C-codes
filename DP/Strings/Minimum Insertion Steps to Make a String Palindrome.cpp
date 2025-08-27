class Solution {
public:

    // LCS (Longest Common Subsequence) nikalne ka function
    // Yaha pe hum do strings le rahe hain: s1 (reversed string) aur s2 (original string)
    // LCS nikalne se hume pata chalega ki kitna bada palindromic subsequence already hai
    int lcs(string s1, string s2){
        int n = s1.size(), m = s2.size();
        
        // DP ke liye 2 arrays use kar rahe hain - space optimized approach
        vector<int> prev(m+1, 0), curr(m+1, 0);

        // DP table fill kar rahe hain
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                // Agar dono characters match karte hain toh 1 add karenge previous diagonal value se
                if(s1[i-1] == s2[j-1]){
                    curr[j] = 1 + prev[j-1];
                }
                else{
                    // Nahi match karte toh max lenge left ya upar wali value ka
                    curr[j] = max(prev[j], curr[j-1]);
                }
            }
            // Current row ko previous row bana do next iteration ke liye
            prev = curr;
        }
        // Last row ka last value hi answer hai (LCS ka length)
        return prev[m];
    }

    // Longest Palindromic Subsequence nikalne ka function
    // Palindrome ka matlab hai string aur uska reverse same hona chahiye
    // Isliye hum string ko reverse kar ke LCS nikal rahe hain
    int longestPalindromeSubseq(string s) {
        string t = s; // Original string ko store kar liya
        reverse(s.begin(), s.end()); // String ko reverse kar diya
        return lcs(s, t); // LCS nikal liya reversed aur original ka
    }

    // Minimum insertions nikalne ka function
    // Formula: total length - longest palindromic subsequence
    // Jitna part already palindrome hai, utna toh insert nahi karna padega
    // Baaki characters ko insert karna padega palindrome banane ke liye
    int minInsertions(string s) {
        return s.size() - longestPalindromeSubseq(s);
    }
};