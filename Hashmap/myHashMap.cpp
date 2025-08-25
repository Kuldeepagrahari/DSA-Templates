#include<bits/stdc++.h>
using namespace std;

const int SIZE = 10;
// Arr[SIZE] = {Node* = ref to a node}
// 0 -> {20, 1} -> {30, 2}
// 1 -> {11, 2} -> {1, 3} -> {21, 3}
// 2 -> {12, 3} -> {32, 34} 
// 3 -> {23, 24}
// .
// .
// .
// .
// .

template<typename K, typename V>
class Node {
public:
    K key;
    V value;
    Node<K, V>* next;
    Node(K key, V value) {
        this -> key = key;
        this -> value = value;
        next = nullptr;
    }
};


template<typename K, typename V>
class HashMap {
private:

    Node<K, V>* table[SIZE];
    int hash(string key) {
        int hashed = 0;
        for(char ch : key) {
            hashed += ch;
        }
        return hashed % SIZE;
    }
    int hash(int key) {
        return key % SIZE;
    }

public:
    HashMap() {
        for (int i = 0; i < SIZE; i++) table[i] = nullptr;
    }

    void Traverse() {
        for(int i = 0; i < SIZE; i++) {
            Node<K, V>* node = table[i];
            cout << i << ":";
            while(node) {
                cout << "(" << node -> key << " " << node -> value << ") ";
                node = node -> next;
            }
            cout << endl;
        }
    }

    // Always table[hashedKey] = reference to most recent node you have inserted
    void insert(K key, V value) {
        int hashedKey = hash(key);
        Node<K, V>* node = new Node<K, V>(key, value);
        node -> next = table[hashedKey];
        table[hashedKey] = node;
    }
    
    V getValue(K key) {
        int hashedKey = hash(key);
        Node<K, V>* head = table[hashedKey];
        while(head != nullptr) {
            if(head -> key == key)
                return head -> value;
            head = head -> next;
        }
        return -1;
    }

    void removeKey(K key) {
        int hashedKey = hash(key);
        Node<K, V>* head = table[hashedKey];
        Node<K, V>* prev = nullptr;

        while(head != nullptr) {
            if(head -> key == key) {
                if(prev)
                    prev -> next = head -> next;

                // if first node is the target node then store the next pointer as the reference to first node 
                table[hashedKey] = head -> next;
                delete head;
                return;
            }
            prev = head;
            head = head -> next;
        }
        cout << "This key  is not present in the map\n";
    }

};

int main() {

    HashMap<int, int> mp;
    HashMap<string, int> mp2;
  
    mp.insert(1, 3);
    mp.insert(20, 45);
    mp.insert(23, 4);
    mp.insert(45, 5);

    mp.Traverse();
    mp.removeKey(20);
    mp.Traverse();
    
    cout << "-------------------------------------\n";

    mp2.insert("sam", 106);
    mp2.insert("kuldeep", 144);
    mp2.Traverse();

    cout << mp2.getValue("sam") << endl;
    cout << mp2.getValue("ansh") << endl;

    mp2.removeKey("kuldeep");
    mp2.Traverse();
}