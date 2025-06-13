
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<int> adj[N];
bool visited[N];


// ================================
// Tree / BST / AVL Tree Templates
// ================================

// 1. Binary Tree Node Structure
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// BST Specific Templates

// 1. Insert into BST
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

// 2. Search in BST
bool searchBST(TreeNode* root, int val) {
    if (!root) return false;
    if (val == root->val) return true;
    return val < root->val ? searchBST(root->left, val) : searchBST(root->right, val);
}

// 3. Delete Node from BST
TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return root;
    if (key < root->val) root->left = deleteNode(root->left, key);
    else if (key > root->val) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        TreeNode* minLargerNode = root->right;
        while (minLargerNode->left) minLargerNode = minLargerNode->left;
        root->val = minLargerNode->val;
        root->right = deleteNode(root->right, minLargerNode->val);
    }
    return root;
}

// 4. Validate BST
bool isValidBST(TreeNode* root, TreeNode* minNode = NULL, TreeNode* maxNode = NULL) {
    if (!root) return true;
    if ((minNode && root->val <= minNode->val) || (maxNode && root->val >= maxNode->val)) return false;
    return isValidBST(root->left, minNode, root) && isValidBST(root->right, root, maxNode);
}

// 5. Lowest Common Ancestor in BST
TreeNode* lcaBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return NULL;
    if (p->val < root->val && q->val < root->val) return lcaBST(root->left, p, q);
    if (p->val > root->val && q->val > root->val) return lcaBST(root->right, p, q);
    return root;
}

// 6. Kth Smallest Element in BST
int kthSmallest(TreeNode* root, int& k) {
    if (!root) return -1;
    int left = kthSmallest(root->left, k);
    if (k == 0) return left;
    if (--k == 0) return root->val;
    return kthSmallest(root->right, k);
}

// 7. Kth Largest in BST
int kthLargest(TreeNode* root, int& k) {
    if (!root) return -1;
    int right = kthLargest(root->right, k);
    if (k == 0) return right;
    if (--k == 0) return root->val;
    return kthLargest(root->left, k);
}

// 8. Find Inorder Predecessor
TreeNode* inorderPredecessor(TreeNode* root, TreeNode* p) {
    TreeNode* pred = NULL;
    while (root) {
        if (p->val > root->val) {
            pred = root;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return pred;
}

// 9. Find Inorder Successor
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* succ = NULL;
    while (root) {
        if (p->val < root->val) {
            succ = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return succ;
}

// 10. Convert BST to Greater Tree
void convertBST(TreeNode* root, int& sum) {
    if (!root) return;
    convertBST(root->right, sum);
    sum += root->val;
    root->val = sum;
    convertBST(root->left, sum);
}

// 11. Trim BST in range [L, R]
TreeNode* trimBST(TreeNode* root, int L, int R) {
    if (!root) return NULL;
    if (root->val < L) return trimBST(root->right, L, R);
    if (root->val > R) return trimBST(root->left, L, R);
    root->left = trimBST(root->left, L, R);
    root->right = trimBST(root->right, L, R);
    return root;
}

// 12. BST Iterator
class BSTIterator {
    stack<TreeNode*> stk;
public:
    BSTIterator(TreeNode* root) {
        while (root) {
            stk.push(root);
            root = root->left;
        }
    }
    int next() {
        TreeNode* node = stk.top(); stk.pop();
        int res = node->val;
        node = node->right;
        while (node) {
            stk.push(node);
            node = node->left;
        }
        return res;
    }
    bool hasNext() {
        return !stk.empty();
    }
};

// 13. Convert Sorted Array to BST
TreeNode* sortedArrayToBST(vector<int>& nums, int l = 0, int r = -1) {
    if (r == -1) r = nums.size() - 1;
    if (l > r) return NULL;
    int m = (l + r) / 2;
    TreeNode* root = new TreeNode(nums[m]);
    root->left = sortedArrayToBST(nums, l, m - 1);
    root->right = sortedArrayToBST(nums, m + 1, r);
    return root;
}

// 14. Recover BST (Two swapped nodes)
void recoverBST(TreeNode* root, TreeNode*& prev, TreeNode*& first, TreeNode*& second) {
    if (!root) return;
    recoverBST(root->left, prev, first, second);
    if (prev && root->val < prev->val) {
        if (!first) first = prev;
        second = root;
    }
    prev = root;
    recoverBST(root->right, prev, first, second);
}

// 15. Find Mode in BST
void findMode(TreeNode* root, int& maxCount, int& currCount, TreeNode*& prev, vector<int>& res) {
    if (!root) return;
    findMode(root->left, maxCount, currCount, prev, res);
    if (prev && prev->val == root->val) currCount++;
    else currCount = 1;
    if (currCount > maxCount) {
        maxCount = currCount;
        res = {root->val};
    } else if (currCount == maxCount) {
        res.push_back(root->val);
    }
    prev = root;
    findMode(root->right, maxCount, currCount, prev, res);
}

// 16. Inorder Morris Traversal
void morrisInorder(TreeNode* root) {
    TreeNode *curr = root, *pre;
    while (curr) {
        if (!curr->left) {
            cout << curr->val << " ";
            curr = curr->right;
        } else {
            pre = curr->left;
            while (pre->right && pre->right != curr) pre = pre->right;
            if (!pre->right) {
                pre->right = curr;
                curr = curr->left;
            } else {
                pre->right = NULL;
                cout << curr->val << " ";
                curr = curr->right;
            }
        }
    }
}

// 17. Check Two BSTs Are Identical
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p || !q) return p == q;
    return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

// 18. Convert BST to Circular DLL
void bstToDLL(TreeNode* root, TreeNode*& head, TreeNode*& prev) {
    if (!root) return;
    bstToDLL(root->left, head, prev);
    if (!prev) head = root;
    else {
        prev->right = root;
        root->left = prev;
    }
    prev = root;
    bstToDLL(root->right, head, prev);
}

// 19. Count Nodes in BST (or Perfect BT)
int countNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// 20. BST to Min Heap
void inorderStore(TreeNode* root, vector<int>& vals) {
    if (!root) return;
    inorderStore(root->left, vals);
    vals.push_back(root->val);
    inorderStore(root->right, vals);
}
void bstToMinHeap(TreeNode* root, vector<int>& vals, int& i) {
    if (!root) return;
    root->val = vals[i++];
    bstToMinHeap(root->left, vals, i);
    bstToMinHeap(root->right, vals, i);
}

int numTrees(int n) {
    vector<int> dp(n + 1, 0);
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i] += dp[j - 1] * dp[i - j];
        }
    }
    return dp[n];
}

// 2. BST + Binary Search + Prefix Sum: Range Sum Query
class RangeSumBST {
    set<int> vals;
    unordered_map<int, int> prefixSum;
public:
    void insert(int val) {
        vals.insert(val);
        int sum = 0;
        for (int x : vals) {
            sum += x;
            prefixSum[x] = sum;
        }
    }
    int rangeSum(int L, int R) {
        auto itL = vals.lower_bound(L);
        auto itR = vals.upper_bound(R);
        if (itL == vals.end() || itR == vals.begin()) return 0;
        --itR;
        return prefixSum[*itR] - (itL == vals.begin() ? 0 : prefixSum[*prev(itL)]);
    }
};

// 3. BST + HashMap: Find Elements appearing more than once
void findDuplicates(TreeNode* root, unordered_map<int, int>& freq) {
    if (!root) return;
    freq[root->val]++;
    findDuplicates(root->left, freq);
    findDuplicates(root->right, freq);
}

// 4. BST + Linked List: Flatten BST to Sorted Linked List
TreeNode* flattenBSTToList(TreeNode* root, TreeNode*& prev) {
    if (!root) return NULL;
    TreeNode* head = flattenBSTToList(root->left, prev);
    if (prev) prev->right = root;
    else head = root;
    root->left = NULL;
    prev = root;
    flattenBSTToList(root->right, prev);
    return head;
}

// 5. BST + Path Tracking: Find all paths from root to leaf
void findAllPaths(TreeNode* root, vector<int>& path, vector<vector<int>>& paths) {
    if (!root) return;
    path.push_back(root->val);
    if (!root->left && !root->right) paths.push_back(path);
    else {
        findAllPaths(root->left, path, paths);
        findAllPaths(root->right, path, paths);
    }
    path.pop_back();
}

// 6. BST + DFS + Greedy: Find Closest K values to a target
void closestKValues(TreeNode* root, double target, int k, deque<int>& dq) {
    if (!root) return;
    closestKValues(root->left, target, k, dq);
    if (dq.size() < k) dq.push_back(root->val);
    else if (abs(dq.front() - target) > abs(root->val - target)) {
        dq.pop_front();
        dq.push_back(root->val);
    } else return;
    closestKValues(root->right, target, k, dq);
}

// 7. BST + Binary Lifting: LCA in BST with Preprocessing
const int LOG = 17;
int up[N][LOG], depth[N];
void dfsLCA(TreeNode* node, TreeNode* parent) {
    if (!node) return;
    up[node->val][0] = parent ? parent->val : -1;
    for (int j = 1; j < LOG; ++j)
        if (up[node->val][j - 1] != -1)
            up[node->val][j] = up[up[node->val][j - 1]][j - 1];
    if (node->left) depth[node->left->val] = depth[node->val] + 1, dfsLCA(node->left, node);
    if (node->right) depth[node->right->val] = depth[node->val] + 1, dfsLCA(node->right, node);
}

// 8. BST + DFS + Backtracking: All paths with given sum
void pathSum(TreeNode* root, int target, vector<int>& path, vector<vector<int>>& res) {
    if (!root) return;
    path.push_back(root->val);
    target -= root->val;
    if (!root->left && !root->right && target == 0) res.push_back(path);
    pathSum(root->left, target, path, res);
    pathSum(root->right, target, path, res);
    path.pop_back();
}

// 9. BST + Serialization
void serialize(TreeNode* root, string& s) {
    if (!root) { s += "# "; return; }
    s += to_string(root->val) + " ";
    serialize(root->left, s);
    serialize(root->right, s);
}
TreeNode* deserialize(istringstream& ss) {
    string val; ss >> val;
    if (val == "#") return NULL;
    TreeNode* root = new TreeNode(stoi(val));
    root->left = deserialize(ss);
    root->right = deserialize(ss);
    return root;
}

// 10. BST + Dynamic Connectivity (Union of disjoint BSTs)
// Dummy union-find-based simulation
int parent[N];
int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}
void unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px != py) parent[px] = py;
}
void initDSU(int n) {
    for (int i = 0; i < n; ++i) parent[i] = i;
}
