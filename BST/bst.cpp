class BST {
    public:
        TreeNode* insert(TreeNode* root, int key) {
            if (!root) return new TreeNode(key);
            if (key < root->val) root->left = insert(root->left, key);
            else root->right = insert(root->right, key);
            return root;
        }
    
        bool search(TreeNode* root, int key) {
            if (!root) return false;
            if (root->val == key) return true;
            return key < root->val ? search(root->left, key) : search(root->right, key);
        }
    };
    