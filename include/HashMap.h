#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <string>
#include <functional>

// Entry for chaining (collision resolution)
template<typename V>
struct HashEntry {
    std::string key;
    V value;
    HashEntry* next;
    
    HashEntry(const std::string& k, const V& v) 
        : key(k), value(v), next(nullptr) {}
};

// HashMap with chaining for O(1) lookup
template<typename V>
class HashMap {
private:
    HashEntry<V>** buckets;
    size_t bucketCount;
    size_t itemCount;
    
    // Simple hash function
    size_t hash(const std::string& key) const {
        std::hash<std::string> hasher;
        return hasher(key) % bucketCount;
    }
    
public:
    HashMap(size_t size = 101) : bucketCount(size), itemCount(0) {
        buckets = new HashEntry<V>*[bucketCount];
        for (size_t i = 0; i < bucketCount; i++) {
            buckets[i] = nullptr;
        }
    }
    
    ~HashMap() {
        for (size_t i = 0; i < bucketCount; i++) {
            HashEntry<V>* entry = buckets[i];
            while (entry != nullptr) {
                HashEntry<V>* temp = entry;
                entry = entry->next;
                delete temp;
            }
        }
        delete[] buckets;
    }
    
    // Insert or update
    void put(const std::string& key, const V& value) {
        size_t index = hash(key);
        HashEntry<V>* entry = buckets[index];
        
        // Check if key already exists
        while (entry != nullptr) {
            if (entry->key == key) {
                entry->value = value;  // Update existing
                return;
            }
            entry = entry->next;
        }
        
        // Insert new entry at beginning of chain
        HashEntry<V>* newEntry = new HashEntry<V>(key, value);
        newEntry->next = buckets[index];
        buckets[index] = newEntry;
        itemCount++;
    }
    
    // Get value (returns nullptr if not found)
    V* get(const std::string& key) {
        size_t index = hash(key);
        HashEntry<V>* entry = buckets[index];
        
        while (entry != nullptr) {
            if (entry->key == key) {
                return &(entry->value);
            }
            entry = entry->next;
        }
        
        return nullptr;  // Not found
    }
    
    // Check if key exists
    bool contains(const std::string& key) const {
        size_t index = hash(key);
        HashEntry<V>* entry = buckets[index];
        
        while (entry != nullptr) {
            if (entry->key == key) {
                return true;
            }
            entry = entry->next;
        }
        
        return false;
    }
    
    // Remove entry
    bool remove(const std::string& key) {
        size_t index = hash(key);
        HashEntry<V>* entry = buckets[index];
        HashEntry<V>* prev = nullptr;
        
        while (entry != nullptr) {
            if (entry->key == key) {
                if (prev == nullptr) {
                    // First in chain
                    buckets[index] = entry->next;
                } else {
                    prev->next = entry->next;
                }
                delete entry;
                itemCount--;
                return true;
            }
            prev = entry;
            entry = entry->next;
        }
        
        return false;  // Not found
    }
    
    // Statistics
    size_t size() const { return itemCount; }
    bool isEmpty() const { return itemCount == 0; }
    
    // Get load factor (for performance analysis)
    float loadFactor() const {
        return static_cast<float>(itemCount) / bucketCount;
    }
    
    // Count collisions (for demo/testing)
    int countCollisions() const {
        int collisions = 0;
        for (size_t i = 0; i < bucketCount; i++) {
            HashEntry<V>* entry = buckets[i];
            int chainLength = 0;
            while (entry != nullptr) {
                chainLength++;
                entry = entry->next;
            }
            if (chainLength > 1) {
                collisions += (chainLength - 1);
            }
        }
        return collisions;
    }
};

#endif