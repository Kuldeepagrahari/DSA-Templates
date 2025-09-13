#include<bits/stdc++.h>
using namespace std;

class MaxHeap {
    int capacity = 1000;
    int curSize;
    int *arr;

    bool nodeExist(int node) {
        return node < curSize;
    }
    void TopDown_Heapify(int node) {
        int parent = node;
        int left_child = 2 * node + 1, right_child = 2 * node + 2;
        int largest_node = parent;

        if(nodeExist(left_child) && arr[left_child] > arr[largest_node]) {
            largest_node = left_child;
        }
        if(nodeExist(right_child) && arr[right_child] > arr[largest_node]) {
            largest_node = right_child;
        }

        if(largest_node != parent) {
            swap(arr[parent], arr[largest_node]);
            TopDown_Heapify(largest_node);
        }
        return;
    }

    void DownTop_Heapify(int node) {
        int parent = (node - 1) / 2;
        if(arr[parent] < arr[node]) {
            swap(arr[parent], arr[node]);
            DownTop_Heapify(parent);
        }
        return;
    }

public:
    MaxHeap() {
        this -> curSize = 0;
        arr = new int[capacity];
    }

    void build_Heap(vector<int> &v) {
        for(int )
    }

    void Push(int val) {
        arr[curSize] = val;
        curSize++;
        DownTop_Heapify(curSize - 1);
    }

    void Pop() {
        int last_node = arr[curSize - 1];
        arr[0] = last_node;
        curSize --;
        TopDown_Heapify(0);
    }

    int Top() {
        return arr[0];
    }

    void print_elements() {
        cout << "MaxHeap or Priority Queue : \n";
        for(int i = 0; i < curSize; i++) cout << arr[i] << " ";
        cout << endl;
    }

};

class HeapSort : public MaxHeap {
public:
    HeapSort(vector<int> &v) {
        Sort(v);
    }

    void Sort(vector<int> &v) {
        build_Heap(v);
        for(int i = v.size() - 1; i >= 0; i--) {
            v[i] = Top();
            Pop();
        }
    }
    
};

void print(vector<int>& v) {
    for(int &x: v) cout << x << " ";
    cout << endl;
}
int main() {
    MaxHeap pq = MaxHeap();
    pq.Push(1);
    pq.Push(3);
    pq.print_elements();
    pq.Push(10);
    pq.Push(7);
    pq.print_elements();
    vector<int> v = {3, 5, 1, 2, 89};
    HeapSort hs = HeapSort(v);
    print(v);

}