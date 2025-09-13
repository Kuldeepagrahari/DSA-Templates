#include<bits/stdc++.h>
using namespace std;

class MinHeap {
    int arr[100];
    int size;

    void heapifyUp(int i) {
        while (i > 0 && arr[i] < arr[(i - 1) / 2]) {
            swap(arr[i], arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void heapifyDown(int i) {
        int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
        if (left < size && arr[left] < arr[smallest]) smallest = left;
        if (right < size && arr[right] < arr[smallest]) smallest = right;
        if (smallest != i) {
            std::swap(arr[i], arr[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap() : size(0) {}

    void push(int val) {
        arr[size++] = val;
        heapifyUp(size - 1);
    }

    int pop() {
        if (size == 0) return -1;
        int minVal = arr[0];
        arr[0] = arr[--size];
        heapifyDown(0);
        return minVal;
    }

    int top() {
        return size ? arr[0] : -1;
    }
};

int main() {

}
