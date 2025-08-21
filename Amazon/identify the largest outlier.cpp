#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;    
class Solution {
public:
    int getLargestOutlier(vector<int>& nums) {
        long long total = 0;
        unordered_map<int,int> mp;

        // Calculate total sum and mpuency
        for(int num : nums){
            total += num;
            mp[num]++;
        }

        sort(nums.begin(), nums.end()); // sorting kar rahe hain taaki largest outlier mil sake
        // End se traverse karenge taaki largest outlier mil sake
        // Agar total sum me se current number minus karen aur woh even ho aur uska aadha map me exist karta ho, toh aisa kyu kar rahe hain?
        // Kyunki hume ek special number chahiye jo n - 2 numbers ke sum ke barabar ho
        // Matlab special number + n - 2 numbers ka sum, n - 1 numbers ke sum ke barabar hai
        // Agar yeh condition satisfy hoti hai, toh current number outlier hai
        // Toh current number hi largest outlier hai
        // Nahi toh agla largest number check karte hain
        // Agar koi outlier nahi mila toh -1 return karenge

        for(int i = nums.size() - 1; i >= 0 ; i--){
            int temp = total - nums[i];
            // temproratily remove the current number from the map
            // kyunki hume check karna hai ki kya baaki numbers ka sum even hai
            mp[nums[i]]--;
            
            // Agar total - nums[i] even hai aur uska half map me exist karta hai
            // toh current number outlier hai
            if(temp % 2 == 0 && mp[temp/2] > 0){
                return nums[i];
            }
            // wapas current number ko map me daal do
            mp[nums[i]]++;
        }
        return -1;
    }
};


// agr n - 2 + special number + outlier = total sum
// we sort the array because if we add the smallers one and special number tbhi last wala sum aayega milla kar
// now we check for outlier last wale el ko htaya and check ki bche hue numbers ka sum 
// hum 2 hisson me baat skte hai ki nhi agr haan toh mtlb speicial number + n - 2 numbers ka sum hai voh
//then check ki voh aadha number map me exist karta hai ya nhi
// agar exist karta hai toh jo number humne - kara tha voh outlier hai
