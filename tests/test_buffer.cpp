#include <iostream>
#include <fstream>
#include <cstring> 
#include "../include/BufferPool.h"

int main() {
    std::cout << "Testing Buffer Pool with LRU Eviction...\n\n";
    
    // Create log file
    std::ofstream logFile("logs/buffer_test.log");
    
    // Create small buffer (only 3 pages) to force evictions
    BufferPool buffer(3, &logFile);
    
    std::cout << "=== Test 1: Access pages (no eviction yet) ===\n";
    char* page1 = buffer.getPage(1);
    strcpy(page1, "Page 1 data");
    
    char* page2 = buffer.getPage(2);
    strcpy(page2, "Page 2 data");
    
    char* page3 = buffer.getPage(3);
    strcpy(page3, "Page 3 data");
    
    std::cout << "Accessed pages 1, 2, 3\n\n";
    
    std::cout << "=== Test 2: Buffer full! Access page 4 ===\n";
    char* page4 = buffer.getPage(4);  // This should evict page 1 (LRU)
    strcpy(page4, "Page 4 data");
    std::cout << "Page 4 loaded (page 1 should be evicted)\n\n";
    
    std::cout << "=== Test 3: Access page 2 again (already in buffer) ===\n";
    char* page2_again = buffer.getPage(2);  // Page hit!
    std::cout << "Page 2 data: " << page2_again << "\n\n";
    
    std::cout << "=== Test 4: Access page 5 ===\n";
    char* page5 = buffer.getPage(5);  // Should evict page 3 (LRU)
    strcpy(page5, "Page 5 data");
    std::cout << "Page 5 loaded (page 3 should be evicted)\n\n";
    
    buffer.printStats();
    
    logFile.close();
    
    std::cout << "\nBuffer Pool test complete!\n";
    std::cout << "Check logs/buffer_test.log for detailed execution log\n";
    
    return 0;
}