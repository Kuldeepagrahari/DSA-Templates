class SegmentTree {
    int* tree;
    int n;
public:
    SegmentTree(int arr[], int size) {
        n = size;
        tree = new int[4 * n];
        build(arr, 0, n - 1, 0);
    }
    void build(int arr[], int l, int r, int i) {
        if (l == r) {
            tree[i] = arr[l];
            return;
        }
        int m = (l + r) / 2;
        build(arr, l, m, 2*i+1);
        build(arr, m+1, r, 2*i+2);
        tree[i] = tree[2*i+1] + tree[2*i+2];
    }
    int query(int ql, int qr) {
        return queryUtil(0, n-1, ql, qr, 0);
    }
    int queryUtil(int l, int r, int ql, int qr, int i) {
        if (ql <= l && qr >= r) return tree[i];
        if (qr < l || ql > r) return 0;
        int m = (l + r) / 2;
        return queryUtil(l, m, ql, qr, 2*i+1) + queryUtil(m+1, r, ql, qr, 2*i+2);
    }
};
