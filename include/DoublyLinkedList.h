#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

// Node for doubly linked list (used in LRU cache)
template<typename T>
struct DLLNode {
    T data;
    DLLNode* prev;
    DLLNode* next;
    
    DLLNode(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

// Doubly Linked List for O(1) LRU operations
template<typename T>
class DoublyLinkedList {
private:
    DLLNode<T>* head;  // Most recently used
    DLLNode<T>* tail;  // Least recently used
    int count;
    
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    
    ~DoublyLinkedList() {
        while (head != nullptr) {
            DLLNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // Add to front (most recently used)
    DLLNode<T>* addToFront(const T& value) {
        DLLNode<T>* newNode = new DLLNode<T>(value);
        
        if (head == nullptr) {
            // Empty list
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        count++;
        return newNode;
    }
    
    // Move existing node to front (mark as recently used)
    void moveToFront(DLLNode<T>* node) {
        if (node == head) return;  // Already at front
        
        // Remove from current position
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        if (node == tail) tail = node->prev;
        
        // Add to front
        node->prev = nullptr;
        node->next = head;
        head->prev = node;
        head = node;
    }
    
    // Remove node (O(1) - we have the node pointer!)
    void remove(DLLNode<T>* node) {
        if (node == nullptr) return;
        
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        
        if (node == head) head = node->next;
        if (node == tail) tail = node->prev;
        
        delete node;
        count--;
    }
    
    // Remove from tail (evict LRU)
    T removeTail() {
        if (tail == nullptr) {
            throw std::runtime_error("List is empty");
        }
        
        T value = tail->data;
        DLLNode<T>* oldTail = tail;
        
        if (head == tail) {
            // Only one node
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        
        delete oldTail;
        count--;
        return value;
    }
    
    // Accessors
    DLLNode<T>* getHead() const { return head; }
    DLLNode<T>* getTail() const { return tail; }
    int size() const { return count; }
    bool isEmpty() const { return count == 0; }
    
    // Print list (for debugging)
    void print() const {
        DLLNode<T>* current = head;
        std::cout << "HEAD -> ";
        while (current != nullptr) {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "TAIL" << std::endl;
    }
};

#endif