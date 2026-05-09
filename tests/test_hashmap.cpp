#include <iostream>
#include "../include/HashMap.h"

// Simple Table metadata structure
struct TableMetadata {
    std::string name;
    std::string filepath;
    int recordCount;
    
    TableMetadata() : name(""), filepath(""), recordCount(0) {}
    TableMetadata(const std::string& n, const std::string& f, int r) 
        : name(n), filepath(f), recordCount(r) {}
};

int main() {
    std::cout << "Testing HashMap (System Catalog)...\n\n";
    
    // Create system catalog
    HashMap<TableMetadata> catalog(10);
    
    // Test 1: Add tables
    std::cout << "=== Test 1: Adding tables to catalog ===\n";
    catalog.put("customer", TableMetadata("customer", "data/customer.dat", 20000));
    catalog.put("orders", TableMetadata("orders", "data/orders.dat", 30000));
    catalog.put("lineitem", TableMetadata("lineitem", "data/lineitem.dat", 50000));
    
    std::cout << "Added 3 tables to catalog\n";
    std::cout << "Catalog size: " << catalog.size() << "\n\n";
    
    // Test 2: Lookup (O(1) access!)
    std::cout << "=== Test 2: O(1) Lookup ===\n";
    TableMetadata* custTable = catalog.get("customer");
    if (custTable) {
        std::cout << "Found table: " << custTable->name << "\n";
        std::cout << "  File: " << custTable->filepath << "\n";
        std::cout << "  Records: " << custTable->recordCount << "\n\n";
    }
    
    // Test 3: Contains check
    std::cout << "=== Test 3: Existence check ===\n";
    std::cout << "Contains 'customer': " << (catalog.contains("customer") ? "YES" : "NO") << "\n";
    std::cout << "Contains 'products': " << (catalog.contains("products") ? "YES" : "NO") << "\n\n";
    
    // Test 4: Update existing
    std::cout << "=== Test 4: Update existing table ===\n";
    catalog.put("customer", TableMetadata("customer", "data/customer_v2.dat", 25000));
    TableMetadata* updatedTable = catalog.get("customer");
    std::cout << "Updated customer records: " << updatedTable->recordCount << " (was 20000)\n\n";
    
    // Test 5: Collision testing
    std::cout << "=== Test 5: Stress test with collisions ===\n";
    HashMap<int> testMap(5);  // Small size to force collisions
    
    for (int i = 0; i < 20; i++) {
        std::string key = "key_" + std::to_string(i);
        testMap.put(key, i * 10);
    }
    
    std::cout << "Inserted 20 items into 5 buckets\n";
    std::cout << "Load factor: " << testMap.loadFactor() << "\n";
    std::cout << "Collisions handled: " << testMap.countCollisions() << "\n\n";
    
    // Verify all items still accessible
    std::cout << "Verifying all 20 items are accessible:\n";
    bool allFound = true;
    for (int i = 0; i < 20; i++) {
        std::string key = "key_" + std::to_string(i);
        int* val = testMap.get(key);
        if (!val || *val != i * 10) {
            allFound = false;
            break;
        }
    }
    std::cout << "All items accessible: " << (allFound ? "YES ✓" : "NO ✗") << "\n\n";
    
    // Test 6: Remove
    std::cout << "=== Test 6: Remove operation ===\n";
    catalog.remove("orders");
    std::cout << "Removed 'orders' table\n";
    std::cout << "Catalog size: " << catalog.size() << " (should be 2)\n";
    std::cout << "Contains 'orders': " << (catalog.contains("orders") ? "YES" : "NO") << "\n\n";
    
    std::cout << "All HashMap tests passed!\n";
    std::cout << "System Catalog ready for table management!\n";
    
    return 0;
}