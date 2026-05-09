#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <string>
#include <stdexcept>

// Query with priority
struct Query {
    std::string command;
    int priority;  // Higher = more urgent (admin = 100, user = 1)
    
    Query() : command(""), priority(0) {}
    Query(const std::string& cmd, int pri) : command(cmd), priority(pri) {}
};

// Priority Queue using Binary Max-Heap
class PriorityQueue {
private:
    Query* heap;
    int capacity;
    int size;
    
    // Get parent/child indices
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    // Swap two queries
    void swap(int i, int j) {
        Query temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }
    
    // Bubble up (fix heap after insertion)
    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)].priority < heap[index].priority) {
            swap(index, parent(index));
            index = parent(index);
        }
    }
    
    // Bubble down (fix heap after removal)
    void heapifyDown(int index) {
        int maxIndex = index;
        int left = leftChild(index);
        int right = rightChild(index);
        
        if (left < size && heap[left].priority > heap[maxIndex].priority) {
            maxIndex = left;
        }
        
        if (right < size && heap[right].priority > heap[maxIndex].priority) {
            maxIndex = right;
        }
        
        if (index != maxIndex) {
            swap(index, maxIndex);
            heapifyDown(maxIndex);
        }
    }
    
    // Resize array when full
    void resize() {
        int newCapacity = capacity * 2;
        Query* newHeap = new Query[newCapacity];
        
        for (int i = 0; i < size; i++) {
            newHeap[i] = heap[i];
        }
        
        delete[] heap;
        heap = newHeap;
        capacity = newCapacity;
    }
    
public:
    PriorityQueue(int initialCapacity = 100) : capacity(initialCapacity), size(0) {
        heap = new Query[capacity];
    }
    
    ~PriorityQueue() {
        delete[] heap;
    }
    
    // Insert query with priority
    void enqueue(const std::string& command, int priority) {
        if (size >= capacity) {
            resize();
        }
        
        heap[size] = Query(command, priority);
        heapifyUp(size);
        size++;
    }
    
    // Remove and return highest priority query
    Query dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        
        Query result = heap[0];
        heap[0] = heap[size - 1];
        size--;
        
        if (size > 0) {
            heapifyDown(0);
        }
        
        return result;
    }
    
    // Peek at highest priority
    Query peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        return heap[0];
    }
    
    bool isEmpty() const {
        return size == 0;
    }
    
    int getSize() const {
        return size;
    }
};

#endif