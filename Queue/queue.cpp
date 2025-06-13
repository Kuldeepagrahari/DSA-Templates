class Queue {
    private:
        Node *front, *rear;
    
    public:
        Queue() : front(nullptr), rear(nullptr) {}
    
        void enqueue(int val) {
            Node* newNode = new Node(val);
            if (!rear) {
                front = rear = newNode;
                return;
            }
            rear->next = newNode;
            rear = newNode;
        }
    
        void dequeue() {
            if (!front) return;
            Node* temp = front;
            front = front->next;
            if (!front) rear = nullptr;
            delete temp;
        }
    
        int peek() {
            return front ? front->data : -1;
        }
    
        bool isEmpty() {
            return front == nullptr;
        }
    };
    