#include <unordered_map>
#include <list>
#include <map>
using namespace std;

class LFUCache {
private:
    int capacity; // cache ki maximum capacity
    int currSize; // abhi cache me kitne elements hai
    
    // key -> iterator (iterator uss key ke node ko point karta hai jo list me pada hai)
    unordered_map<int, list<vector<int>>::iterator> keyNode;
    
    // frequency -> list of {key, value, freq}
    // list ka front = sabse recently use hua, back = sabse least recently use hua
    map<int, list<vector<int>>> freqList;
    
public:
    LFUCache(int cap) {
        capacity = cap;
        currSize = 0;
    }
    
    // Jab bhi key access/update hoti hai toh uski frequency badh jaati hai
    void updateFrequency(int key) {
        auto &node = *(keyNode[key]); // node = {key, value, freq}
        
        int value = node[1];
        int f     = node[2];
        
        // purani frequency wali list se hatao
        freqList[f].erase(keyNode[key]);
        
        if(freqList[f].empty())
            freqList.erase(f); // agar list empty ho gayi toh us frequency ko bhi hata do
        
        f++; // frequency 1 badhao
        
        // naye frequency group me front me daal do (front = MRU)
        freqList[f].push_front({key, value, f});
        
        // mapping update karo
        keyNode[key] = freqList[f].begin();
    }
    
    int get(int key) {
        if(keyNode.find(key) == keyNode.end())
            return -1; // key nahi mili
        
        auto &node = *(keyNode[key]);
        int value = node[1];
        
        // access hua toh frequency badh jaayegi
        updateFrequency(key);
        
        return value;
    }
    
    void put(int key, int value) {
        if(capacity == 0)
            return; // edge case: agar capacity 0 hai toh kuch store hi nahi hoga
        
        if(keyNode.find(key) != keyNode.end()) {
            // key already exist karti hai → value update karo aur frequency badhao
            auto &node = *(keyNode[key]);
            node[1] = value;
            updateFrequency(key);
        }
        else if(currSize < capacity) {
            // abhi jagah khali hai → naya element daal do frequency = 1 ke sath
            currSize++;
            freqList[1].push_front({key, value, 1});
            keyNode[key] = freqList[1].begin();
        }
        else {
            // cache full hai → LFU (least freq) ko nikalna padega
            // agar tie hai toh uss frequency group ka LRU (back me jo hoga) nikalega
            auto &listRef = freqList.begin()->second; // sabse chhoti freq ki list
            
            int keyToRemove = listRef.back()[0]; // back = sabse purana use hua
            
            listRef.pop_back();
            if(listRef.empty())
                freqList.erase(freqList.begin()->first);
            
            // naya element freq=1 ke sath daal do
            freqList[1].push_front({key, value, 1});
            
            // mapping update karo
            keyNode.erase(keyToRemove);
            keyNode[key] = freqList[1].begin();
        }
    }
};
