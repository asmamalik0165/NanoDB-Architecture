#include "../include/BufferPool.h"
#include <iostream>
#include <cstring>

BufferPool::BufferPool(size_t numPages, std::ofstream* log) 
    : numPages(numPages), logFile(log), pageFaults(0), evictions(0) {
    
    // Allocate raw memory block
    memory = new char[numPages * PAGE_SIZE];
    memset(memory, 0, numPages * PAGE_SIZE);
    
    // Allocate page table
    pageTable = new PageFrame[numPages];
    for (size_t i = 0; i < numPages; i++) {
        pageTable[i].data = memory + (i * PAGE_SIZE);
    }
    
    if (logFile && logFile->is_open()) {
        *logFile << "[BUFFER] Initialized buffer pool: " 
                 << numPages << " pages × " << PAGE_SIZE 
                 << " bytes = " << (numPages * PAGE_SIZE / 1024) << " KB\n";
    }
    
    std::cout << "[BUFFER] Pool initialized with " << numPages << " pages\n";
}

BufferPool::~BufferPool() {
    flushAll();  // Write dirty pages before shutdown
    delete[] memory;
    delete[] pageTable;
}

int BufferPool::findFreePage() {
    // Find unused frame
    for (size_t i = 0; i < numPages; i++) {
        if (pageTable[i].pageId == -1) {
            return i;
        }
    }
    return -1;  // No free frames
}

int BufferPool::evictLRU() {
    if (lruList.isEmpty()) {
        throw std::runtime_error("Cannot evict: no pages in buffer");
    }
    
    // Get LRU page (tail of list)
    int pageId = lruList.removeTail();
    
    // Find frame containing this page
    for (size_t i = 0; i < numPages; i++) {
        if (pageTable[i].pageId == pageId) {
            // Write to disk if dirty
            if (pageTable[i].isDirty) {
                writeToDisk(i);
            }
            
            if (logFile && logFile->is_open()) {
                *logFile << "[EVICT] Page " << pageId 
                         << " evicted via LRU from frame " << i << "\n";
            }
            
            evictions++;
            pageTable[i].pageId = -1;  // Mark as free
            pageTable[i].lruNode = nullptr;
            return i;
        }
    }
    
    return -1;
}

void BufferPool::writeToDisk(int frameId) {
    // Simulate disk write (in real DB, this writes to actual file)
    std::string filename = "data/page_" + std::to_string(pageTable[frameId].pageId) + ".dat";
    std::ofstream file(filename, std::ios::binary);
    
    if (file.is_open()) {
        file.write(pageTable[frameId].data, PAGE_SIZE);
        file.close();
        
        if (logFile && logFile->is_open()) {
            *logFile << "[DISK] Page " << pageTable[frameId].pageId 
                     << " written to disk: " << filename << "\n";
        }
        
        pageTable[frameId].isDirty = false;
    }
}

void BufferPool::readFromDisk(int pageId, int frameId) {
    // Simulate disk read
    std::string filename = "data/page_" + std::to_string(pageId) + ".dat";
    std::ifstream file(filename, std::ios::binary);
    
    if (file.is_open()) {
        file.read(pageTable[frameId].data, PAGE_SIZE);
        file.close();
        
        if (logFile && logFile->is_open()) {
            *logFile << "[DISK] Page " << pageId 
                     << " read from disk: " << filename << "\n";
        }
    } else {
        // Page doesn't exist on disk - initialize with zeros
        memset(pageTable[frameId].data, 0, PAGE_SIZE);
    }
}

char* BufferPool::getPage(int pageId) {
    // Check if page already in buffer
    for (size_t i = 0; i < numPages; i++) {
        if (pageTable[i].pageId == pageId) {
            // Page hit! Move to front of LRU
            if (pageTable[i].lruNode) {
                lruList.moveToFront(pageTable[i].lruNode);
            }
            return pageTable[i].data;
        }
    }
    
    // Page fault! Need to load from disk
    pageFaults++;
    
    if (logFile && logFile->is_open()) {
        *logFile << "[FAULT] Page " << pageId << " not in buffer (page fault #" 
                 << pageFaults << ")\n";
    }
    
    // Find free frame or evict
    int frameId = findFreePage();
    if (frameId == -1) {
        frameId = evictLRU();
    }
    
    // Load page from disk
    readFromDisk(pageId, frameId);
    pageTable[frameId].pageId = pageId;
    pageTable[frameId].isDirty = false;
    
    // Add to front of LRU list
    pageTable[frameId].lruNode = lruList.addToFront(pageId);
    
    return pageTable[frameId].data;
}

void BufferPool::markDirty(int pageId) {
    for (size_t i = 0; i < numPages; i++) {
        if (pageTable[i].pageId == pageId) {
            pageTable[i].isDirty = true;
            
            if (logFile && logFile->is_open()) {
                *logFile << "[DIRTY] Page " << pageId << " marked as dirty\n";
            }
            return;
        }
    }
}

void BufferPool::flushAll() {
    int flushed = 0;
    for (size_t i = 0; i < numPages; i++) {
        if (pageTable[i].pageId != -1 && pageTable[i].isDirty) {
            writeToDisk(i);
            flushed++;
        }
    }
    
    if (logFile && logFile->is_open()) {
        *logFile << "[FLUSH] Flushed " << flushed << " dirty pages to disk\n";
    }
}

void BufferPool::printStats() const {
    std::cout << "\n=== Buffer Pool Statistics ===\n";
    std::cout << "Page Faults: " << pageFaults << "\n";
    std::cout << "Evictions: " << evictions << "\n";
    std::cout << "==============================\n";
}