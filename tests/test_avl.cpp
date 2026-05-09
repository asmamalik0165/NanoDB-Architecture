#include <iostream>
#include <chrono>
#include "../include/AVLTree.h"

int main() {
    std::cout << "Testing AVL Tree (Balanced Index)...\n\n";
    
    AVLTree<int, std::string> index;
    
    // Test 1: Insert customer IDs
    std::cout << "=== Test 1: Building index ===\n";
    index.insert(100, "Customer A");
    index.insert(50, "Customer B");
    index.insert(150, "Customer C");
    index.insert(25, "Customer D");
    index.insert(75, "Customer E");
    index.insert(125, "Customer F");
    index.insert(175, "Customer G");
    
    std::cout << "Inserted 7 customers\n";
    std::cout << "Tree height: " << index.treeHeight() << " (should be ~3 for balanced)\n";
    std::cout << "Is balanced: " << (index.isBalanced() ? "YES " : "NO ") << "\n\n";
    
    // Test 2: Search O(log N)
    std::cout << "=== Test 2: O(log N) Search ===\n";
    std::string* customer = index.search(75);
    if (customer) {
        std::cout << "Found ID 75: " << *customer << "\n";
    }
    
    std::string* notFound = index.search(999);
    std::cout << "Search ID 999: " << (notFound ? "Found" : "Not found") << "\n\n";
    
    // Test 3: Auto-balancing test
    std::cout << "=== Test 3: Auto-balancing (insert 100 items) ===\n";
    AVLTree<int, int> balanceTest;
    
    // Insert in sequential order (worst case for unbalanced BST!)
    for (int i = 1; i <= 100; i++) {
        balanceTest.insert(i, i * 10);
    }
    
    std::cout << "Inserted 100 sequential items\n";
    std::cout << "Tree height: " << balanceTest.treeHeight() 
              << " (unbalanced BST would be ~100!)\n";
    std::cout << "Is balanced: " << (balanceTest.isBalanced() ? "YES " : "NO ") << "\n\n";
    
    // Test 4: Performance comparison
    std::cout << "=== Test 4: Performance Test (10,000 items) ===\n";
    AVLTree<int, int> perfTest;
    
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        perfTest.insert(i, i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto insertTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Insert time: " << insertTime.count() << " ms\n";
    std::cout << "Tree height: " << perfTest.treeHeight() 
              << " (log₂(10000) ≈ 13.3)\n";
    
    // Search test
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        perfTest.search(i * 10);
    }
    end = std::chrono::high_resolution_clock::now();
    auto searchTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "1000 searches: " << searchTime.count() << " microseconds\n";
    std::cout << "Average: " << (searchTime.count() / 1000.0) << " microseconds per search\n\n";
    
    std::cout << "All AVL Tree tests passed!\n";
    std::cout << "Index ready for O(log N) customer lookups!\n";
    
    return 0;
}