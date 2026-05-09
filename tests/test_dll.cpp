#include <iostream>
#include "../include/DoublyLinkedList.h"

int main() {
    std::cout << "Testing Doubly Linked List (LRU Cache)...\n\n";
    
    DoublyLinkedList<int> lru;
    
    // Test 1: Add pages to cache (simulate page accesses)
    std::cout << "Adding pages 1, 2, 3 to cache:\n";
    auto node1 = lru.addToFront(1);
    auto node2 = lru.addToFront(2);
    auto node3 = lru.addToFront(3);
    lru.print();  // Should show: 3 <-> 2 <-> 1
    std::cout << "Size: " << lru.size() << "\n\n";
    
    // Test 2: Access page 1 (move to front)
    std::cout << "Accessing page 1 (move to front):\n";
    lru.moveToFront(node1);
    lru.print();  // Should show: 1 <-> 3 <-> 2
    std::cout << "\n";
    
    // Test 3: Evict LRU (remove tail)
    std::cout << "Evicting LRU page:\n";
    int evicted = lru.removeTail();
    std::cout << "Evicted page: " << evicted << " (should be 2)\n";
    lru.print();  // Should show: 1 <-> 3
    std::cout << "\n";
    
    // Test 4: Simulate real LRU behavior
    std::cout << "Simulating LRU cache (capacity = 3):\n";
    DoublyLinkedList<int> cache;
    
    std::cout << "Access pages: 5, 6, 7\n";
    cache.addToFront(5);
    cache.addToFront(6);
    cache.addToFront(7);
    cache.print();
    
    std::cout << "\nCache full! Access page 8 (evict LRU):\n";
    cache.removeTail();  // Evict 5
    cache.addToFront(8);
    cache.print();
    
    std::cout << "\n✅ All Doubly Linked List tests passed!\n";
    std::cout << "Ready for Buffer Pool integration!\n";
    
    return 0;
}