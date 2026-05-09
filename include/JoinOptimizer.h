#ifndef JOIN_OPTIMIZER_H
#define JOIN_OPTIMIZER_H

#include <string>
#include <iostream>
#include <algorithm>

// Edge in the join graph (represents a join operation)
struct JoinEdge {
    int table1;
    int table2;
    double cost;  // Estimated join cost (based on table sizes)
    
    JoinEdge() : table1(-1), table2(-1), cost(0.0) {}
    JoinEdge(int t1, int t2, double c) : table1(t1), table2(t2), cost(c) {}
};

// Union-Find data structure for MST (cycle detection)
class UnionFind {
private:
    int* parent;
    int* rank;
    int size;
    
public:
    UnionFind(int n) : size(n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    
    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) {
            return false;  // Already in same set (would create cycle)
        }
        
        // Union by rank
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        
        return true;
    }
};

class JoinOptimizer {
private:
    std::string* tableNames;
    int numTables;
    JoinEdge* edges;
    int numEdges;
    
    // Sort edges by cost (for Kruskal's algorithm)
    void sortEdges() {
        // Simple bubble sort (good enough for small number of edges)
        for (int i = 0; i < numEdges - 1; i++) {
            for (int j = 0; j < numEdges - i - 1; j++) {
                if (edges[j].cost > edges[j + 1].cost) {
                    JoinEdge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }
    }
    
public:
    JoinOptimizer(int maxTables = 10, int maxEdges = 50) 
        : numTables(0), numEdges(0) {
        tableNames = new std::string[maxTables];
        edges = new JoinEdge[maxEdges];
    }
    
    ~JoinOptimizer() {
        delete[] tableNames;
        delete[] edges;
    }
    
    // Add table to join graph
    int addTable(const std::string& name) {
        tableNames[numTables] = name;
        return numTables++;
    }
    
    // Add join edge (potential join between two tables)
    void addJoin(int table1, int table2, double cost) {
        edges[numEdges++] = JoinEdge(table1, table2, cost);
    }
    
    // Find optimal join order using Kruskal's MST algorithm
    void findOptimalJoinOrder(JoinEdge* mstEdges, int& mstSize) {
        mstSize = 0;
        
        // Sort edges by cost (ascending)
        sortEdges();
        
        // Union-Find for cycle detection
        UnionFind uf(numTables);
        
        // Kruskal's algorithm
        for (int i = 0; i < numEdges && mstSize < numTables - 1; i++) {
            JoinEdge& edge = edges[i];
            
            // If adding this edge doesn't create a cycle
            if (uf.unite(edge.table1, edge.table2)) {
                mstEdges[mstSize++] = edge;
            }
        }
    }
    
    // Print join order
    void printJoinOrder(const JoinEdge* mstEdges, int mstSize) {
        std::cout << "Optimal Join Order (MST):\n";
        double totalCost = 0.0;
        
        for (int i = 0; i < mstSize; i++) {
            std::cout << "  " << tableNames[mstEdges[i].table1] 
                      << " -> " << tableNames[mstEdges[i].table2]
                      << " (cost: " << mstEdges[i].cost << ")\n";
            totalCost += mstEdges[i].cost;
        }
        
        std::cout << "Total estimated cost: " << totalCost << "\n";
    }
    
    // Generate log entry (for demo)
    void generateLog(const JoinEdge* mstEdges, int mstSize, std::ostream& log) {
        log << "[OPTIMIZER] Multi-table join optimization using MST\n";
        log << "[OPTIMIZER] Tables involved: ";
        for (int i = 0; i < numTables; i++) {
            log << tableNames[i];
            if (i < numTables - 1) log << ", ";
        }
        log << "\n";
        
        log << "[OPTIMIZER] Optimal join path:\n";
        for (int i = 0; i < mstSize; i++) {
            log << "[OPTIMIZER]   " << tableNames[mstEdges[i].table1]
                << " -> " << tableNames[mstEdges[i].table2]
                << " (cost: " << mstEdges[i].cost << ")\n";
        }
    }
    
    std::string getTableName(int index) const {
        return tableNames[index];
    }
};

#endif