

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<int> adj[N];
bool visited[N];


// ================================
// Hashing Templates (Hash Maps, Sets, Rolling Hashes, Open Addressing, etc.)
// ================================

// 1. Frequency Counter using Hash Map
unordered_map<int, int> freqCounter(vector<int>& nums) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;
    return freq;
}

// 2. Count Distinct Elements
int countDistinct(vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    return s.size();
}

// 3. Detect Cycle using Union-Find with Path Compression
int find(int x, vector<int>& parent) {
    if (parent[x] != x) parent[x] = find(parent[x], parent);
    return parent[x];
}
void unite(int x, int y, vector<int>& parent) {
    int px = find(x, parent), py = find(y, parent);
    if (px != py) parent[px] = py;
}

// 4. Custom Hash Function (for pair<int, int>)
struct custom_hash {
    size_t operator()(pair<int, int> p) const {
        return hash<long long>()(((long long)p.first << 32) ^ p.second);
    }
};

// 5. Group Anagrams using Sorted String Hash
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> mp;
    for (auto& s : strs) {
        string t = s;
        sort(t.begin(), t.end());
        mp[t].push_back(s);
    }
    vector<vector<string>> res;
    for (auto& p : mp) res.push_back(p.second);
    return res;
}

// 6. Two Sum using Hash Map
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mp;
    for (int i = 0; i < nums.size(); ++i) {
        int rem = target - nums[i];
        if (mp.count(rem)) return {mp[rem], i};
        mp[nums[i]] = i;
    }
    return {};
}

// 7. Longest Consecutive Sequence
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    int longest = 0;
    for (int x : s) {
        if (!s.count(x - 1)) {
            int len = 1;
            while (s.count(x + len)) len++;
            longest = max(longest, len);
        }
    }
    return longest;
}

// 8. Rolling Hash (Rabin-Karp for string matching)
const int base = 31, mod = 1e9 + 7;
vector<long long> computeHash(string& s) {
    int n = s.size();
    vector<long long> hash(n + 1), power(n + 1);
    power[0] = 1;
    for (int i = 0; i < n; ++i) {
        hash[i + 1] = (hash[i] * base + s[i] - 'a' + 1) % mod;
        power[i + 1] = (power[i] * base) % mod;
    }
    return hash;
}
long long getHash(vector<long long>& hash, vector<long long>& power, int l, int r) {
    return (hash[r] - hash[l] * power[r - l] % mod + mod) % mod;
}

// 9. Open Addressing - Linear Probing
struct HashTableLP {
    int size = 10007;
    vector<int> table;
    HashTableLP() : table(size, -1) {}
    void insert(int key) {
        int i = key % size;
        while (table[i] != -1) i = (i + 1) % size;
        table[i] = key;
    }
    bool search(int key) {
        int i = key % size, start = i;
        while (table[i] != -1) {
            if (table[i] == key) return true;
            i = (i + 1) % size;
            if (i == start) break;
        }
        return false;
    }
};

// 10. Quadratic Probing
struct HashTableQP {
    int size = 10007;
    vector<int> table;
    HashTableQP() : table(size, -1) {}
    void insert(int key) {
        int i = key % size, j = 0;
        while (table[(i + j * j) % size] != -1) ++j;
        table[(i + j * j) % size] = key;
    }
    bool search(int key) {
        int i = key % size, j = 0;
        while (table[(i + j * j) % size] != -1 && j < size) {
            if (table[(i + j * j) % size] == key) return true;
            ++j;
        }
        return false;
    }
};

// 11. Double Hashing
struct HashTableDH {
    int size = 10007;
    vector<int> table;
    HashTableDH() : table(size, -1) {}
    int h1(int key) { return key % size; }
    int h2(int key) { return 7 - (key % 7); }
    void insert(int key) {
        int i = h1(key), j = 0;
        while (table[(i + j * h2(key)) % size] != -1) ++j;
        table[(i + j * h2(key)) % size] = key;
    }
    bool search(int key) {
        int i = h1(key), j = 0;
        while (table[(i + j * h2(key)) % size] != -1 && j < size) {
            if (table[(i + j * h2(key)) % size] == key) return true;
            ++j;
        }
        return false;
    }
};

// 12. Subarray Sum = K (Prefix Sum + HashMap)
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> mp;
    mp[0] = 1;
    int sum = 0, count = 0;
    for (int x : nums) {
        sum += x;
        count += mp[sum - k];
        mp[sum]++;
    }
    return count;
}

// 13. HashSet for Duplicate Detection in O(1)
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> s;
    for (int x : nums) {
        if (s.count(x)) return true;
        s.insert(x);
    }
    return false;
}

// 14. Count Pairs with Given XOR
int countPairsXOR(vector<int>& nums, int k) {
    unordered_map<int, int> mp;
    int count = 0;
    for (int x : nums) {
        count += mp[x ^ k];
        mp[x]++;
    }
    return count;
}

// 15. Find All Duplicates in Array
vector<int> findDuplicates(vector<int>& nums) {
    unordered_map<int, int> mp;
    vector<int> res;
    for (int x : nums) {
        if (++mp[x] == 2) res.push_back(x);
    }
    return res;
}

// 16. Hash String to Integer (Polynomial Rolling Hash)
long long polyHash(string& s) {
    const int base = 31;
    const long long mod = 1e9 + 9;
    long long hash = 0, power = 1;
    for (char c : s) {
        hash = (hash + (c - 'a' + 1) * power) % mod;
        power = (power * base) % mod;
    }
    return hash;
}

// 17. Detect Palindromic Substrings using Hashing
// (Compare hashes of prefix & reversed prefix)

// 18. Distinct Substrings Count using Rolling Hash + Set
int countDistinctSubstrings(string& s) {
    int n = s.size();
    unordered_set<long long> hashes;
    for (int len = 1; len <= n; ++len) {
        vector<long long> h = computeHash(s);
        vector<long long> p(n + 1);
        p[0] = 1;
        for (int i = 1; i <= n; ++i) p[i] = (p[i - 1] * base) % mod;
        for (int i = 0; i <= n - len; ++i) {
            hashes.insert(getHash(h, p, i, i + len));
        }
    }
    return hashes.size();
}

// 19. Detect Substring using Rolling Hash
bool matchSubstring(string& s, string& t) {
    int n = s.size(), m = t.size();
    vector<long long> hs = computeHash(s);
    vector<long long> ht = computeHash(t);
    vector<long long> power(n + 1);
    power[0] = 1;
    for (int i = 1; i <= n; ++i) power[i] = (power[i - 1] * base) % mod;
    long long hashT = getHash(ht, power, 0, m);
    for (int i = 0; i <= n - m; ++i) {
        if (getHash(hs, power, i, i + m) == hashT) return true;
    }
    return false;
}

// 20. Implement Your Own Hash Map
struct MyHashMap {
    static const int SIZE = 10007;
    vector<pair<int, int>> table[SIZE];
    int hash(int key) { return key % SIZE; }

    void put(int key, int value) {
        int h = hash(key);
        for (auto& p : table[h]) {
            if (p.first == key) {
                p.second = value;
                return;
            }
        }
        table[h].emplace_back(key, value);
    }

    int get(int key) {
        int h = hash(key);
        for (auto& p : table[h]) {
            if (p.first == key) return p.second;
        }
        return -1;
    }

    void remove(int key) {
        int h = hash(key);
        auto& bucket = table[h];
        bucket.erase(remove_if(bucket.begin(), bucket.end(), [&](auto& p) { return p.first == key; }), bucket.end());
    }
};
