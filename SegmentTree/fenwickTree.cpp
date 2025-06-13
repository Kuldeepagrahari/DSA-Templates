class FenwickTree {
    int* bit, n;
public:
    FenwickTree(int size) {
        n = size;
        bit = new int[n+1]();
    }
    void update(int i, int val) {
        for (; i <= n; i += i & -i) bit[i] += val;
    }
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) sum += bit[i];
        return sum;
    }
};
