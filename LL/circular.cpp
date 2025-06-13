struct CNode {
    int data;
    CNode* next;
    CNode(int val) : data(val), next(NULL) {}
};

class CircularLinkedList {
    CNode* tail;
public:
    CircularLinkedList() : tail(NULL) {}
    void insert(int val) {
        CNode* node = new CNode(val);
        if (!tail) {
            node->next = node;
            tail = node;
        } else {
            node->next = tail->next;
            tail->next = node;
            tail = node;
        }
    }
    void display() {
        if (!tail) return;
        CNode* curr = tail->next;
        do {
            cout << curr->data << " -> ";
            curr = curr->next;
        } while (curr != tail->next);
        cout << "(head)\n";
    }
};