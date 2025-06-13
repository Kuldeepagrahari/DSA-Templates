// ================================
// Complete Graph Algorithms Template
// ================================

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<int> adj[N];
bool visited[N];



// 1. KMP Prefix Table
vector<int> kmpPrefix(string& s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

// 2. Z-Algorithm (Z-array)
vector<int> zFunction(string& s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

// 3. Suffix Array (O(n log n))
vector<int> buildSuffixArray(string s) {
    s += '$';
    int n = s.size();
    vector<int> sa(n), c(n), cnt(max(256, n));
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < 256; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) sa[--cnt[s[i]]] = i;
    c[sa[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[sa[i]] != s[sa[i - 1]]) classes++;
        c[sa[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = sa[i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--cnt[c[pn[i]]]] = pn[i];
        cn[sa[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[sa[i]], c[(sa[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[sa[i - 1]], c[(sa[i - 1] + (1 << h)) % n]};
            if (cur != prev) ++classes;
            cn[sa[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return sa;
}

// 4. LCP Array (Kasai’s Algorithm)
vector<int> buildLCP(string& s, vector<int>& sa) {
    int n = s.size();
    vector<int> rank(n), lcp(n);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    for (int i = 0, k = 0; i < n; i++) {
        if (rank[i] == n - 1) { k = 0; continue; }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank[i]] = k;
        if (k) k--;
    }
    return lcp;
}

// 5. Manacher’s Algorithm (Longest Palindromic Substring in O(n))
vector<int> manacher(string s) {
    string t = "#";
    for (char c : s) t += c, t += "#";
    int n = t.size(), center = 0, right = 0;
    vector<int> p(n);
    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * center - i;
        if (i < right) p[i] = min(right - i, p[mirror]);
        while (i + p[i] + 1 < n && i - p[i] - 1 >= 0 && t[i + p[i] + 1] == t[i - p[i] - 1]) p[i]++;
        if (i + p[i] > right) center = i, right = i + p[i];
    }
    return p;
}

// 6. Trie Data Structure
struct TrieNode {
    TrieNode* children[26] = {};
    bool isEnd = false;
};

class Trie {
public:
    TrieNode* root = new TrieNode();
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (!node->children[i]) node->children[i] = new TrieNode();
            node = node->children[i];
        }
        node->isEnd = true;
    }
    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (!node->children[i]) return false;
            node = node->children[i];
        }
        return node->isEnd;
    }
};

// 7. Minimum Characters to Append to Make Palindrome
int minCharsToMakePalindrome(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    string combined = s + '#' + rev;
    vector<int> pi = kmpPrefix(combined);
    return s.size() - pi.back();
}

// 8. Longest Repeated Substring using Suffix Array + LCP
string longestRepeatedSubstring(string s) {
    auto sa = buildSuffixArray(s);
    auto lcp = buildLCP(s + '$', sa);
    int idx = max_element(lcp.begin(), lcp.end()) - lcp.begin();
    return s.substr(sa[idx], lcp[idx]);
}

// 9. Find All Occurrences of Pattern (Z-algorithm)
vector<int> findPatternZ(string text, string pattern) {
    string combined = pattern + "$" + text;
    vector<int> z = zFunction(combined);
    vector<int> indices;
    for (int i = pattern.size() + 1; i < z.size(); ++i)
        if (z[i] == pattern.size()) indices.push_back(i - pattern.size() - 1);
    return indices;
}

// 10. Count of Distinct Substrings using Suffix Array + LCP
int countDistinctSubstrSA(string s) {
    s += '$';
    auto sa = buildSuffixArray(s);
    auto lcp = buildLCP(s, sa);
    int n = s.size(), res = 0;
    for (int i = 1; i < n; i++) res += n - sa[i] - 1 - lcp[i - 1];
    return res;
}


vector<int> zFunction(string& s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

// 2. KMP Prefix Function
vector<int> kmpPrefix(string& s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

// 3. Rabin-Karp Multiple Pattern Matching
vector<int> rabinKarp(string& text, string& pat) {
    const int base = 31, mod = 1e9 + 9;
    int n = text.size(), m = pat.size();
    long long pHash = 0, power = 1;
    for (char c : pat) {
        pHash = (pHash * base + c - 'a' + 1) % mod;
        power = (power * base) % mod;
    }
    long long tHash = 0;
    vector<int> matches;
    for (int i = 0; i < n; ++i) {
        tHash = (tHash * base + text[i] - 'a' + 1) % mod;
        if (i >= m - 1) {
            if (i >= m) tHash = (tHash - (text[i - m] - 'a' + 1) * power % mod + mod) % mod;
            if (tHash == pHash) matches.push_back(i - m + 1);
        }
    }
    return matches;
}

// 4. Manacher's Algorithm (Longest Palindromic Substring in Linear Time)
string longestPalindrome(string s) {
    string t = "#";
    for (char c : s) t += c, t += "#";
    int n = t.size(), center = 0, right = 0, maxLen = 0, idx = 0;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        int mirror = 2 * center - i;
        if (i < right) p[i] = min(right - i, p[mirror]);
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n && t[i - p[i] - 1] == t[i + p[i] + 1]) ++p[i];
        if (i + p[i] > right) center = i, right = i + p[i];
        if (p[i] > maxLen) maxLen = p[i], idx = i;
    }
    return s.substr((idx - maxLen) / 2, maxLen);
}

// 5. Suffix Array (O(n log n))
vector<int> buildSuffixArray(string s) {
    s += "$";
    int n = s.size(), k = 0;
    vector<int> sa(n), c(n);
    iota(sa.begin(), sa.end(), 0);
    sort(sa.begin(), sa.end(), [&](int a, int b) { return s[a] < s[b]; });
    for (int i = 1; i < n; ++i) c[sa[i]] = c[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    for (k = 0; (1 << k) < n; ++k) {
        vector<int> sa2(n);
        for (int i = 0; i < n; ++i) sa2[i] = (sa[i] - (1 << k) + n) % n;
        vector<int> cnt(n);
        for (int x : c) ++cnt[x];
        for (int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) sa[--cnt[c[sa2[i]]]] = sa2[i];
        vector<int> c2(n);
        c2[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            pair<int, int> prev = {c[sa[i - 1]], c[(sa[i - 1] + (1 << k)) % n]};
            pair<int, int> now = {c[sa[i]], c[(sa[i] + (1 << k)) % n]};
            c2[sa[i]] = c2[sa[i - 1]] + (now != prev);
        }
        c = c2;
    }
    return sa;
}

// 6. Longest Common Prefix Array (Kasai’s Algorithm)
vector<int> buildLCP(string& s, vector<int>& sa) {
    int n = s.size();
    vector<int> rank(n), lcp(n - 1);
    for (int i = 0; i < n; ++i) rank[sa[i]] = i;
    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
        lcp[rank[i]] = k;
        if (k) --k;
    }
    return lcp;
}

// 7. Trie (Insert and Search)
struct TrieNode {
    TrieNode* next[26] = {};
    bool isEnd = false;
};

void insertTrie(TrieNode* root, string& word) {
    for (char c : word) {
        if (!root->next[c - 'a']) root->next[c - 'a'] = new TrieNode();
        root = root->next[c - 'a'];
    }
    root->isEnd = true;
}

bool searchTrie(TrieNode* root, string& word) {
    for (char c : word) {
        if (!root->next[c - 'a']) return false;
        root = root->next[c - 'a'];
    }
    return root->isEnd;
}

