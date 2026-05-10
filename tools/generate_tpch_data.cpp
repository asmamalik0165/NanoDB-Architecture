#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

void generateCustomers(const char* filepath, int count) {
    std::ofstream file(filepath);
    
    std::cout << "Generating " << count << " customers...\n";
    
    for (int i = 1; i <= count; i++) {
        file << i << "|"                                        // c_custkey
             << "Customer#" << i << "|"                         // c_name
             << "Address " << i << " Street, City|"            // c_address
             << (rand() % 25) << "|"                            // c_nationkey (0-24)
             << "555-" << (1000 + rand() % 9000) << "|"        // c_phone
             << (rand() % 10000) + (rand() % 100) / 100.0 << "|" // c_acctbal
             << (rand() % 5 == 0 ? "BUILDING" : "AUTOMOBILE") << "|" // c_mktsegment
             << "Regular customer comment\n";                   // c_comment
        
        if (i % 5000 == 0) std::cout << "  " << i << " customers...\n";
    }
    
    file.close();
    std::cout << "✓ customer.tbl created (" << count << " records)\n\n";
}

void generateOrders(const char* filepath, int count, int maxCustKey) {
    std::ofstream file(filepath);
    
    std::cout << "Generating " << count << " orders...\n";
    
    for (int i = 1; i <= count; i++) {
        file << i << "|"                                        // o_orderkey
             << (1 + rand() % maxCustKey) << "|"               // o_custkey
             << (rand() % 3 == 0 ? "O" : "F") << "|"          // o_orderstatus (O=open, F=filled)
             << (rand() % 500000) + (rand() % 100) / 100.0 << "|" // o_totalprice
             << "1995-" << (1 + rand() % 12) << "-" << (1 + rand() % 28) << "|" // o_orderdate
             << "1-URGENT|"                                     // o_orderpriority
             << "Clerk#" << (1 + rand() % 1000) << "|"         // o_clerk
             << (rand() % 3) << "|"                             // o_shippriority
             << "Standard order comment\n";                     // o_comment
        
        if (i % 5000 == 0) std::cout << "  " << i << " orders...\n";
    }
    
    file.close();
    std::cout << "✓ orders.tbl created (" << count << " records)\n\n";
}

void generateLineItems(const char* filepath, int count, int maxOrderKey) {
    std::ofstream file(filepath);
    
    std::cout << "Generating " << count << " line items...\n";
    
    for (int i = 1; i <= count; i++) {
        file << (1 + rand() % maxOrderKey) << "|"              // l_orderkey
             << (1 + rand() % 200000) << "|"                   // l_partkey
             << (1 + rand() % 10000) << "|"                    // l_suppkey
             << (1 + rand() % 7) << "|"                        // l_linenumber
             << (1 + rand() % 50) << "|"                       // l_quantity
             << (rand() % 100000) + (rand() % 100) / 100.0 << "|" // l_extendedprice
             << (rand() % 10) / 100.0 << "|"                   // l_discount
             << (rand() % 8) / 100.0 << "|"                    // l_tax
             << (rand() % 2 == 0 ? "N" : "R") << "|"          // l_returnflag
             << (rand() % 2 == 0 ? "O" : "F") << "|"          // l_linestatus
             << "1995-01-01|1995-02-01|1995-03-01|"           // l_shipdate, commitdate, receiptdate
             << "DELIVER IN PERSON|TRUCK|"                     // l_shipinstruct, l_shipmode
             << "Line item comment\n";                         // l_comment
        
        if (i % 10000 == 0) std::cout << "  " << i << " line items...\n";
    }
    
    file.close();
    std::cout << "✓ lineitem.tbl created (" << count << " records)\n\n";
}

int main() {
    srand(time(nullptr));
    
    std::cout << "########################################\n";
    std::cout << "  TPC-H Data Generator for NanoDB     \n";
    std::cout << "########################################\n\n";
    
    std::cout << "Target: 100,000 total records\n";
    std::cout << "Schema: TPC-H compliant (pipe-delimited)\n\n";
    
    generateCustomers("data/customer.tbl", 20000);
    generateOrders("data/orders.tbl", 30000, 20000);
    generateLineItems("data/lineitem.tbl", 50000, 30000);
    
    std::cout << "#############################\n";
    std::cout << " ✓ TPC-H Data Generation Complete!    \n";
    std::cout << "#############################\n\n";
    
    std::cout << "Summary:\n";
    std::cout << "  customer.tbl   : 20,000 records\n";
    std::cout << "  orders.tbl     : 30,000 records\n";
    std::cout << "  lineitem.tbl   : 50,000 records\n";
    std::cout << "  -------------------------------\n";
    std::cout << "  TOTAL          : 100,000 records\n\n";
    
    std::cout << "Files created in data/ directory\n";
    std::cout << "Ready for NanoDB benchmark!\n";
    
    return 0;
}