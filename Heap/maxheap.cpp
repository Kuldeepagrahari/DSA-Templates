#include<bits/stdc++.h>
using namespace std;

class MaxHeap {
    int* arr;
    int size, cap;
public:
    MaxHeap(int capacity) {
        arr = new int[capacity];
        size = 0; cap = capacity;
    }
    void insert(int val) {
        arr[size] = val;
        int i = size;
        size++;
        while (i > 0 && arr[(i-1)/2] < arr[i]) {
            swap(arr[i], arr[(i-1)/2]);
            i = (i-1)/2;
        }
    }
    void heapify(int i) {
        int largest = i, l = 2*i + 1, r = 2*i + 2;
        if (l < size && arr[l] > arr[largest]) largest = l;
        if (r < size && arr[r] > arr[largest]) largest = r;
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(largest);
        }
    }
    int extractMax() {
        if (size <= 0) return -1;
        int root = arr[0];
        arr[0] = arr[size - 1];
        size--;
        heapify(0);
        return root;
    }
};