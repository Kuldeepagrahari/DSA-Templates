
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(NULL), next(NULL) {}
};

class DoublyLinkedList {
    DNode* head;
public:
    DoublyLinkedList() : head(NULL) {}
    void insertFront(int val) {
        DNode* node = new DNode(val);
        node->next = head;
        if (head) head->prev = node;
        head = node;
    }
    void display() {
        DNode* curr = head;
        while (curr) {
            cout << curr->data << " <-> ";
            curr = curr->next;
        }
        cout << "NULL\n";
    }
};