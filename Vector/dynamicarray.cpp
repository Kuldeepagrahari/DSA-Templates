class DynamicArray {
    private:
        int* arr;
        int cap, size;
    public:
        DynamicArray() {
            cap = 2; size = 0;
            arr = new int[cap];
        }
        void push(int val) {
            if (size == cap) {
                int* temp = new int[cap * 2];
                for (int i = 0; i < cap; ++i) temp[i] = arr[i];
                delete[] arr;
                arr = temp;
                cap *= 2;
            }
            arr[size++] = val;
        }
    };
    
    