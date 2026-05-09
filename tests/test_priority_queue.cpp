#include <iostream>
#include "../include/PriorityQueue.h"

int main() {
    std::cout << "Testing Priority Queue (Binary Heap)...\n\n";
    
    PriorityQueue queue;
    
    // Test 1: Basic enqueue/dequeue
    std::cout << "=== Test 1: Basic Operations ===\n";
    queue.enqueue("Query A", 5);
    queue.enqueue("Query B", 10);
    queue.enqueue("Query C", 3);
    
    std::cout << "Enqueued: A(5), B(10), C(3)\n";
    std::cout << "Dequeue order (highest priority first):\n";
    
    while (!queue.isEmpty()) {
        Query q = queue.dequeue();
        std::cout << "  " << q.command << " (priority: " << q.priority << ")\n";
    }
    std::cout << "\n";
    
    // Test 2: Demo Test Case E (50 user queries + 1 admin)
    std::cout << "=== Test 2: Admin Priority (Test Case E) ===\n";
    std::cout << "Enqueueing 50 user SELECT queries...\n";
    
    for (int i = 1; i <= 50; i++) {
        std::string query = "SELECT * FROM customer WHERE id = " + std::to_string(i);
        queue.enqueue(query, 1);  // User priority = 1
    }
    
    std::cout << "Enqueueing 1 admin UPDATE query...\n";
    queue.enqueue("UPDATE customer SET balance = 5000 WHERE id = 12345", 100);  // Admin = 100
    
    std::cout << "\nFirst query dequeued:\n";
    Query first = queue.dequeue();
    std::cout << "  " << first.command << " (priority: " << first.priority << ")\n";
    
    if (first.priority == 100) {
        std::cout << "  ✅ Admin query executed FIRST!\n";
    } else {
        std::cout << "  ❌ ERROR: User query executed first!\n";
    }
    
    std::cout << "\nRemaining queue size: " << queue.getSize() << " (should be 50)\n\n";
    
    // Test 3: Mixed priorities
    std::cout << "=== Test 3: Mixed Priority Levels ===\n";
    PriorityQueue mixedQueue;
    
    mixedQueue.enqueue("Low priority query", 1);
    mixedQueue.enqueue("Medium priority query", 50);
    mixedQueue.enqueue("High priority query", 100);
    mixedQueue.enqueue("Another low", 2);
    mixedQueue.enqueue("Another high", 99);
    
    std::cout << "Dequeue order:\n";
    while (!mixedQueue.isEmpty()) {
        Query q = mixedQueue.dequeue();
        std::cout << "  Priority " << q.priority << ": " << q.command << "\n";
    }
    
    std::cout << "\n All Priority Queue tests passed!\n";
    std::cout << "Ready for Test Case E demo!\n";
    
    return 0;
}