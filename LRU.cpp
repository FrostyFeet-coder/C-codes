#include <list>
#include <unordered_map>
#include <iostream>
using namespace std;
#include <vector>


// LRU Cache Implementation using Vector (Brute Force Approach)
// Time Complexity: O(n) for both get and put operations
// Space Complexity: O(n) for storing the cache
// Note: This is not optimal for large inputs due to linear search in vector
class LRUCache {
public:
    vector<pair<int,int>> cache; // Vector of {key, value} pairs
    int n; // capacity

    LRUCache(int capacity) {
        n = capacity; // Initialize cache capacity
    }
    
    int get(int key) {
        // Linearly search for key in cache
        for(int i = 0 ; i < cache.size() ; i++){
            if(cache[i].first == key){ 
                int val = cache[i].second; // value mil gayi
                
                pair<int,int> temp = cache[i];  
                cache.erase(cache.begin() + i); // usko purani position se hatao
                cache.push_back(temp); // aur end me daal do (end = most recently used)
                
                return val; // value return karo
            }
        }
        return -1; // key nahi mili toh -1
    }
    
    void put(int key, int value) {
        // Agar key already present hai
        for(int i = 0; i < cache.size(); i++){
            if(cache[i].first == key){ 
                cache.erase(cache.begin() + i); // purana entry hatao
                cache.push_back({key , value}); // naya {key,value} last me daalo (recent banao)
                return ;
            }
        }

        // Agar cache full ho gaya
        if(cache.size() == n){
            cache.erase(cache.begin()); // sabse pehle wale (least recently used) ko hatao
            cache.push_back({key , value}); // naya element last me daalo
        } else {
            // Agar space bacha hai toh seedha add karo
            cache.push_back({key , value});
        }
    }
};




// LRU Cache Implementation using Doubly Linked List and Hash Map OPTIMAL APPROACH
// Time Complexity: O(1) for both get and put operations
class LRUCache {
public:
    int n;
    list<int> dll; // Doubly Linked List: front = most recently used, back = least recently used
    unordered_map<int, pair<list<int>::iterator, int>> mpp; 
    // Map: key -> {address of key in DLL, value}

    LRUCache(int capacity) {
        n = capacity; // max capacity
    }

    void makerecentlyuse(int key) {
        dll.erase(mpp[key].first);   // Purane position se key ko DLL me se hatao
        dll.push_front(key);         // Fir usko front me daal do (most recent ban gaya)
        mpp[key].first = dll.begin(); // Map me bhi naya iterator update kar do
    }

    int get(int key) {
        if (mpp.find(key) == mpp.end()) return -1; // Agar key hi nahi hai -> -1 return

        makerecentlyuse(key); // Key mil gayi toh usko recent banao
        return mpp[key].second; // Value return karo
    }

    void put(int key, int value) {
        if (mpp.find(key) != mpp.end()) { // Agar key already present hai
            mpp[key].second = value;      // Uski value update karo
            makerecentlyuse(key);         // Aur recent banao
            return;
        }

        if ((int)mpp.size() == n) { // Agar cache full hai
            int lru = dll.back();   // Least recent (DLL back) ko nikaalo
            dll.pop_back();         
            mpp.erase(lru);         // Map se bhi usko hatao
        }

        dll.push_front(key);               // Nayi key ko front me daalo
        mpp[key] = {dll.begin(), value};   // Map me nayi entry daalo (address + value)
    }
};

int main() {
    LRUCache cache(2); // Cache capacity = 2

    cache.put(1, 10);
    cache.put(2, 20);
    cout << "get(1): " << cache.get(1) << endl; // returns 10

    cache.put(3, 30); // evicts key 2
    cout << "get(2): " << cache.get(2) << endl; // returns -1 (not found)

    cache.put(4, 40); // evicts key 1
    cout << "get(1): " << cache.get(1) << endl; // returns -1 (not found)
    cout << "get(3): " << cache.get(3) << endl; // returns 30
    cout << "get(4): " << cache.get(4) << endl; // returns 40

    return 0;
}