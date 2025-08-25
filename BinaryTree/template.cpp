// ================================
// Complete Graph Algorithms Template
// ================================

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<int> adj[N];
bool visited[N];

// ================================
// Dynamic Programming Templates
// ================================

// [Already present DP templates... kept unchanged here for brevity.]

// ================================
// Tree / BST / AVL Tree Templates
// ================================

// 1. Binary Tree Node Structure
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 2. Inorder Traversal
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

// 3. Preorder Traversal
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

// 4. Postorder Traversal
void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

// 5. Level Order Traversal
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        res.push_back(level);
    }
    return res;
}

// 6. Max Depth of Binary Tree
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// 7. Insert into BST
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

// 8. Search in BST
bool searchBST(TreeNode* root, int val) {
    if (!root) return false;
    if (val == root->val) return true;
    return val < root->val ? searchBST(root->left, val) : searchBST(root->right, val);
}

// 9. Delete Node from BST
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

// 10. Lowest Common Ancestor (LCA) in BST
TreeNode* lcaBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (p->val < root->val && q->val < root->val)
        return lcaBST(root->left, p, q);
    else if (p->val > root->val && q->val > root->val)
        return lcaBST(root->right, p, q);
    return root;
}

// 11. Check if Balanced Tree
int checkBalanced(TreeNode* root) {
    if (!root) return 0;
    int left = checkBalanced(root->left);
    if (left == -1) return -1;
    int right = checkBalanced(root->right);
    if (right == -1) return -1;
    if (abs(left - right) > 1) return -1;
    return max(left, right) + 1;
}
bool isBalanced(TreeNode* root) {
    return checkBalanced(root) != -1;
}

// 12. Validate BST
bool isValidBST(TreeNode* root, TreeNode* minNode = NULL, TreeNode* maxNode = NULL) {
    if (!root) return true;
    if ((minNode && root->val <= minNode->val) || (maxNode && root->val >= maxNode->val)) return false;
    return isValidBST(root->left, minNode, root) && isValidBST(root->right, root, maxNode);
}

// 13. Diameter of Binary Tree
int diameter(TreeNode* root, int& maxDiameter) {
    if (!root) return 0;
    int left = diameter(root->left, maxDiameter);
    int right = diameter(root->right, maxDiameter);
    maxDiameter = max(maxDiameter, left + right);
    return max(left, right) + 1;
}

// 14. Mirror a Binary Tree
TreeNode* mirror(TreeNode* root) {
    if (!root) return NULL;
    swap(root->left, root->right);
    mirror(root->left);
    mirror(root->right);
    return root;
}

// 15. Path Sum Exists
bool hasPathSum(TreeNode* root, int sum) {
    if (!root) return false;
    if (!root->left && !root->right) return root->val == sum;
    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}

// 16. All Root to Leaf Paths
void dfsPaths(TreeNode* root, vector<int>& path, vector<vector<int>>& res) {
    if (!root) return;
    path.push_back(root->val);
    if (!root->left && !root->right) res.push_back(path);
    dfsPaths(root->left, path, res);
    dfsPaths(root->right, path, res);
    path.pop_back();
}

// 17. Flatten Binary Tree to Linked List (Preorder)
void flatten(TreeNode* root) {
    if (!root) return;
    flatten(root->left);
    flatten(root->right);
    TreeNode* temp = root->right;
    root->right = root->left;
    root->left = NULL;
    TreeNode* t = root;
    while (t->right) t = t->right;
    t->right = temp;
}

// 18. Right Side View of Tree
vector<int> rightSideView(TreeNode* root) {
    vector<int> view;
    if (!root) return view;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; ++i) {
            TreeNode* node = q.front(); q.pop();
            if (i == n - 1) view.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return view;
}

// 19. Tree from Inorder and Preorder
TreeNode* buildTreePreIn(vector<int>& preorder, vector<int>& inorder, int& idx, int l, int r, unordered_map<int, int>& inMap) {
    if (l > r) return NULL;
    int rootVal = preorder[idx++];
    TreeNode* root = new TreeNode(rootVal);
    root->left = buildTreePreIn(preorder, inorder, idx, l, inMap[rootVal] - 1, inMap);
    root->right = buildTreePreIn(preorder, inorder, idx, inMap[rootVal] + 1, r, inMap);
    return root;
}

// 20. Tree to Doubly Linked List (Inorder)
void treeToDLL(TreeNode* root, TreeNode*& head, TreeNode*& prev) {
    if (!root) return;
    treeToDLL(root->left, head, prev);
    if (!prev) head = root;
    else {
        prev->right = root;
        root->left = prev;
    }
    prev = root;
    treeToDLL(root->right, head, prev);
}



// 21. Count Nodes in Complete Binary Tree
int countNodes(TreeNode* root) {
    if (!root) return 0;
    int lh = 0, rh = 0;
    TreeNode* l = root, *r = root;
    while (l) { lh++; l = l->left; }
    while (r) { rh++; r = r->right; }
    if (lh == rh) return (1 << lh) - 1;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// 22. Kth Smallest in BST
int kthSmallest(TreeNode* root, int& k) {
    if (!root) return -1;
    int left = kthSmallest(root->left, k);
    if (k == 0) return left;
    if (--k == 0) return root->val;
    return kthSmallest(root->right, k);
}

// 23. Invert Binary Tree
TreeNode* invertTree(TreeNode* root) {
    if (!root) return NULL;
    swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

// 24. Vertical Order Traversal
vector<vector<int>> verticalOrder(TreeNode* root) {
    map<int, vector<int>> nodes;
    queue<pair<TreeNode*, int>> q;
    if (root) q.push({root, 0});
    while (!q.empty()) {
        auto [node, dist] = q.front(); q.pop();
        nodes[dist].push_back(node->val);
        if (node->left) q.push({node->left, dist - 1});
        if (node->right) q.push({node->right, dist + 1});
    }
    vector<vector<int>> res;
    for (auto& [k, v] : nodes) res.push_back(v);
    return res;
}

// 25. Check if Identical Trees
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q || p->val != q->val) return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}
// Check if Symmetric trees
bool Checker(TreeNode* l, TreeNode* r){
    if(!l && !r) return true;
    else if((l&& !r) || (!l && r)) return false;
    
    if(l -> data != r -> data) return false;
    bool outward = Checker(l -> left, r -> right);
    bool inward = Checker(l -> right, r -> left);
    return inward & outward;
    
}
bool isSymmetric(TreeNode* root) {
    // Code here
    return Checker(root -> left, root -> right);
}
// 26. Binary Tree Maximum Path Sum
int maxPathDown(TreeNode* root, int& maxSum) {
    if (!root) return 0;
    int left = max(0, maxPathDown(root->left, maxSum));
    int right = max(0, maxPathDown(root->right, maxSum));
    maxSum = max(maxSum, left + right + root->val);
    return max(left, right) + root->val;
}

// 27. Tree Serialization
string serialize(TreeNode* root) {
    if (!root) return "#";
    return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
}

// 28. Tree Deserialization
TreeNode* deserializeHelper(queue<string>& nodes) {
    string val = nodes.front(); nodes.pop();
    if (val == "#") return NULL;
    TreeNode* root = new TreeNode(stoi(val));
    root->left = deserializeHelper(nodes);
    root->right = deserializeHelper(nodes);
    return root;
}
TreeNode* deserialize(string data) {
    stringstream ss(data);
    string item;
    queue<string> nodes;
    while (getline(ss, item, ',')) nodes.push(item);
    return deserializeHelper(nodes);
}

// 29. Morris Inorder Traversal (O(1) space)
void morrisInorder(TreeNode* root) {
    TreeNode* curr = root;
    while (curr) {
        if (!curr->left) {
            cout << curr->val << " ";
            curr = curr->right;
        } else {
            TreeNode* pred = curr->left;
            while (pred->right && pred->right != curr) pred = pred->right;
            if (!pred->right) {
                pred->right = curr;
                curr = curr->left;
            } else {
                pred->right = NULL;
                cout << curr->val << " ";
                curr = curr->right;
            }
        }
    }
}

// 30. Count Paths with Sum K
int pathSumUtil(TreeNode* root, int targetSum, unordered_map<int,int>& prefix, int currSum) {
    if (!root) return 0;
    currSum += root->val;
    int res = prefix[currSum - targetSum];
    prefix[currSum]++;
    res += pathSumUtil(root->left, targetSum, prefix, currSum);
    res += pathSumUtil(root->right, targetSum, prefix, currSum);
    prefix[currSum]--;
    return res;
}
int pathSum(TreeNode* root, int sum) {
    unordered_map<int,int> prefix;
    prefix[0] = 1;
    return pathSumUtil(root, sum, prefix, 0);
}
