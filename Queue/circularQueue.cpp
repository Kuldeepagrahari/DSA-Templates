class CircularQueue {
    int* arr, front, rear, size, cap;
public:
    CircularQueue(int c) {
        cap = c;
        arr = new int[c];
        front = rear = -1;
        size = 0;
    }
    bool enqueue(int val) {
        if ((rear + 1) % cap == front) return false;
        if (front == -1) front = 0;
        rear = (rear + 1) % cap;
        arr[rear] = val;
        size++;
        return true;
    }
    bool dequeue() {
        if (front == -1) return false;
        if (front == rear) front = rear = -1;
        else front = (front + 1) % cap;
        size--;
        return true;
    }
};