#ifndef BUFFER_POOL_H
#define BUFFER_POOL_H

#include <fstream>
#include <string>
#include "DoublyLinkedList.h"

// Page metadata
struct PageFrame {
    int pageId;
    bool isDirty;           // Modified but not written to disk?
    char* data;             // Pointer to actual page data
    DLLNode<int>* lruNode;  // Pointer to position in LRU list
    
    PageFrame() : pageId(-1), isDirty(false), data(nullptr), lruNode(nullptr) {}
};

class BufferPool {
private:
    static const size_t PAGE_SIZE = 4096;  // 4KB pages
    
    char* memory;                    // Raw contiguous memory block
    PageFrame* pageTable;            // Metadata for each frame
    size_t numPages;                 // Total frames in buffer
    
    DoublyLinkedList<int> lruList;   // LRU eviction policy
    std::ofstream* logFile;          // Execution log
    
    int pageFaults;                  // Statistics
    int evictions;
    
    // Helper methods
    int findFreePage();
    int evictLRU();
    void writeToDisk(int frameId);
    void readFromDisk(int pageId, int frameId);
    
public:
    BufferPool(size_t numPages, std::ofstream* log);
    ~BufferPool();
    
    // Core operations
    char* getPage(int pageId);        // Get page, load if needed
    void markDirty(int pageId);       // Mark page as modified
    void flushAll();                  // Write all dirty pages
    
    // Statistics
    int getPageFaults() const { return pageFaults; }
    int getEvictions() const { return evictions; }
    void printStats() const;
};

#endif