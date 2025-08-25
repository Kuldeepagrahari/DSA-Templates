#include<bits/stdc++.h>
using namespace std;

const int SIZE = 10;

class HashMap {
private:
    struct Entry {
        int key, value;
        Entry* next;
        Entry(int k, int v) : key(k), value(v), next(nullptr) {}
    };

    Entry* table[SIZE];

    int hash(int key) {
        return key % SIZE;
    }

public:
    HashMap() {
        for (int i = 0; i < SIZE; i++) table[i] = nullptr;
    }

    void insert(int key, int value) {
        int h = hash(key);
        Entry* entry = new Entry(key, value);
        entry->next = table[h];
        table[h] = entry;
    }

    int get(int key) {
        int h = hash(key);
        Entry* curr = table[h];
        while (curr) {
            if (curr->key == key) return curr->value;
            curr = curr->next;
        }
        return -1;
    }

    void remove(int key) {
        int h = hash(key);
        Entry* curr = table[h];
        Entry* prev = nullptr;
        while (curr) {
            if (curr->key == key) {
                if (prev) prev->next = curr->next;
                else table[h] = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }
};
