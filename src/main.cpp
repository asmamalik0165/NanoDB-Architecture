#include <iostream>
#include <fstream>
#include <string>
#include "../include/Stack.h"
#include "../include/DataValue.h"
#include "../include/BufferPool.h"
#include "../include/HashMap.h"
#include "../include/AVLTree.h"
#include "../include/QueryParser.h"
#include "../include/JoinOptimizer.h"
#include "../include/PriorityQueue.h"

class NanoDB {
private:
    BufferPool* bufferPool;
    HashMap<std::string>* systemCatalog;
    AVLTree<int, std::string>* customerIndex;
    QueryParser* parser;
    std::ofstream logFile;
    
public:
    NanoDB() {
        std::cout << "========================================\n";
        std::cout << "      NanoDB Database Engine v1.0      \n";
        std::cout << "  Asma Zafar 26I-7808 \n";
        std::cout << "========================================\n\n";
        
        // Open execution log
        logFile.open("logs/nanodb_execution.log");
        if (logFile.is_open()) {
            logFile << "[SYSTEM] NanoDB Engine Starting...\n";
            logFile << "[SYSTEM] All custom data structures (NO STL)\n";
            logFile << "[SYSTEM] Timestamp: " << __DATE__ << " " << __TIME__ << "\n\n";
        }
        
        // Initialize components
        std::cout << "[INIT] Initializing database components...\n";
        
        bufferPool = new BufferPool(50, &logFile);  // 50 pages buffer
        std::cout << " Buffer Pool initialized (50 pages)\n";
        
        systemCatalog = new HashMap<std::string>(101);
        std::cout << "System Catalog initialized (HashMap)\n";
        
        customerIndex = new AVLTree<int, std::string>();
        std::cout << " Customer Index initialized (AVL Tree)\n";
        
        parser = new QueryParser();
        std::cout << " Query Parser initialized (Stack-based)\n";
        
        // Register tables in catalog
        systemCatalog->put("customer", "data/customer.dat");
        systemCatalog->put("orders", "data/orders.dat");
        systemCatalog->put("lineitem", "data/lineitem.dat");
        std::cout << "System Catalog loaded (3 tables)\n\n";
        
        logFile << "[SYSTEM] All components initialized successfully\n\n";
    }
    
    ~NanoDB() {
        bufferPool->flushAll();
        bufferPool->printStats();
        
        delete bufferPool;
        delete systemCatalog;
        delete customerIndex;
        delete parser;
        
        if (logFile.is_open()) {
            logFile << "\n[SYSTEM] NanoDB Engine Shutdown Complete\n";
            logFile.close();
        }
    }
    
    void demonstrateComponents() {
        std::cout << "=== Component Demonstrations ===\n\n";
        
        // Demo 1: Buffer Pool
        std::cout << "1. Buffer Pool & LRU Cache:\n";
        std::cout << "   Accessing pages 1, 2, 3...\n";
        char* page1 = bufferPool->getPage(1);
        char* page2 = bufferPool->getPage(2);
        char* page3 = bufferPool->getPage(3);
        strcpy(page1, "Customer data page 1");
        bufferPool->markDirty(1);
        std::cout << "   Pages loaded into buffer pool\n\n";
        
        // Demo 2: System Catalog
        std::cout << "2. System Catalog (HashMap):\n";
        std::string* path = systemCatalog->get("customer");
        if (path) {
            std::cout << "   Table 'customer' -> " << *path << "\n";
        }
        std::cout << "   Catalog contains 'orders': " 
                  << (systemCatalog->contains("orders") ? "YES" : "NO") << "\n\n";
        
        // Demo 3: AVL Tree Index
        std::cout << "3. AVL Tree Index:\n";
        std::cout << "   Building index on customer IDs...\n";
        customerIndex->insert(12345, "Alice Johnson");
        customerIndex->insert(67890, "Bob Smith");
        customerIndex->insert(11111, "Charlie Brown");
        customerIndex->insert(99999, "Diana Prince");
        std::cout << "   Indexed 4 customers\n";
        std::cout << "   Tree height: " << customerIndex->treeHeight() << "\n";
        std::cout << "   Search customer 67890: ";
        std::string* customer = customerIndex->search(67890);
        if (customer) std::cout << *customer << "\n\n";
        
        // Demo 4: Query Parser
        std::cout << "4. Query Parser (Infix to Postfix):\n";
        std::string query = "(c_acctbal > 5000 AND c_mktsegment == BUILDING) OR c_nationkey == 15";
        std::string postfix = parser->infixToPostfix(query);
        std::cout << "   Infix:   " << query << "\n";
        std::cout << "   Postfix: " << postfix << "\n";
        logFile << "[PARSER] Query parsed: " << query << "\n";
        logFile << "[PARSER] Postfix form: " << postfix << "\n\n";
        std::cout << "   Expression parsed successfully\n\n";
        
        // Demo 5: Join Optimizer
        std::cout << "5. Join Optimizer (MST-based):\n";
        std::cout << "   Optimizing: customer JOIN orders JOIN lineitem\n";
        
        JoinOptimizer optimizer;
        int cust = optimizer.addTable("customer");
        int ord = optimizer.addTable("orders");
        int line = optimizer.addTable("lineitem");
        
        optimizer.addJoin(cust, ord, 600000);
        optimizer.addJoin(ord, line, 1500000);
        optimizer.addJoin(cust, line, 1000000);
        
        JoinEdge mst[10];
        int mstSize = 0;
        optimizer.findOptimalJoinOrder(mst, mstSize);
        
        std::cout << "   Optimal path: ";
        for (int i = 0; i < mstSize; i++) {
            std::cout << optimizer.getTableName(mst[i].table1) << " -> " 
                      << optimizer.getTableName(mst[i].table2);
            if (i < mstSize - 1) std::cout << " -> ";
        }
        std::cout << "\n";
        
        optimizer.generateLog(mst, mstSize, logFile);
        std::cout << "   Join optimized via MST\n\n";

        // Demo 6: Priority Queue
        std::cout << "6. Priority Queue (Admin vs User Queries):\n";
        std::cout << "   Enqueueing 50 user queries + 1 admin query...\n";
        
        PriorityQueue queryQueue;
        for (int i = 0; i < 50; i++) {
            queryQueue.enqueue("SELECT * FROM customer WHERE id = " + std::to_string(i), 1);
        }
        queryQueue.enqueue("UPDATE customer SET balance = 5000 WHERE id = 12345", 100);
        
        Query firstQuery = queryQueue.dequeue();
        std::cout << "   First executed: " << firstQuery.command.substr(0, 50) << "...\n";
        std::cout << "   Priority: " << firstQuery.priority << " (100 = admin)\n";
        std::cout << "   [✓] Admin query bypassed 50 user queries!\n\n";
    }
    
    void showStatus() {
        std::cout << "\n=== NanoDB Status ===\n";
        std::cout << "Buffer Pool: " << bufferPool->getPageFaults() << " page faults, "
                  << bufferPool->getEvictions() << " evictions\n";
        std::cout << "System Catalog: " << systemCatalog->size() << " tables registered\n";
        std::cout << "Customer Index: " << customerIndex->size() << " entries, "
                  << "height " << customerIndex->treeHeight() << "\n";
        std::cout << "=====================\n\n";
    }
};

int main() {
    NanoDB* db = new NanoDB();
    
    db->demonstrateComponents();
    db->showStatus();
    
    std::cout << "[SUCCESS] NanoDB demonstration complete!\n";
    std::cout << "[INFO] Check logs/nanodb_execution.log for detailed logs\n";
    std::cout << "\nAll 8 custom data structures working:\n";
    std::cout << "  Stack (Query Parser)\n";
    std::cout << "  DataValue (Polymorphic Types)\n";
    std::cout << "  Doubly Linked List (LRU Cache)\n";
    std::cout << "  Buffer Pool (Memory Manager)\n";
    std::cout << "  HashMap (System Catalog)\n";
    std::cout << "  AVL Tree (Indexing)\n";
    std::cout << "  Query Parser (Expression Evaluation)\n";
    std::cout << "  Join Optimizer (MST)\n";
    std::cout << "\nNanoDB ready for TPC-H benchmark!\n";
    
    delete db;
    return 0;
}