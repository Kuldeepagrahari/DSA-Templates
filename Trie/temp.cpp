void update(int *arr, ll *st, ll ss, ll se, ll si, ll index, ll new_val) {
    
    if(ss == se) {
        arr[index] = new_val;
        st[si] = new_val;
        return;
    }
    
    ll mid = (ss + se) / 2;
    
    if(index <= mid)
    {
        update(arr, st, ss, mid, 2 * si + 1, index, new_val);
    }
    else
    {
        update(arr, st, mid + 1, se, 2 * si + 2, index, new_val);
    }
    st[si] = st[2 * si + 1] + st[2 * si + 2];
    
}
void updateValue(int *arr, ll *st, ll n, ll index, ll new_val) {
    // add code here
    update(arr, st, 0, n - 1, 0, index, new_val);
}

// Function to return sum of elements in range from index qs (query start)
// to qe (query end).
ll getSum(ll *st, ll ss, ll se, ll qs, ll qe, ll si) {
    if(qe < ss || se < qs) {
        return 0;
    }
    
    if(qs <= ss && qe >= se) {
        return st[si];
    }
    
    ll mid = (ss + se) / 2;
    
    return getSum(st, ss, mid, qs, qe, 2 * si + 1) + 
        getSum(st, mid + 1, se, qs, qe, 2 * si + 2);
}
ll getsum(ll *st, ll n, ll l, ll r) {
    // add code here
    return getSum(st, 0, n - 1, l, r, 0);
}
