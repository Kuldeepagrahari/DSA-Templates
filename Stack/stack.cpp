class Stack {
    private:
        Node* top;
    
    public:
        Stack() : top(nullptr) {}
    
        void push(int val) {
            Node* newNode = new Node(val);
            newNode->next = top;
            top = newNode;
        }
    
        void pop() {
            if (!top) return;
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    
        int peek() {
            return top ? top->data : -1;
        }
    
        bool isEmpty() {
            return top == nullptr;
        }
    };
    