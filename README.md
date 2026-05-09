# NanoDB - Custom Database Engine

Implementing a mini database system from scratch with custom data structures (NO STL).

## 🎯 Project Overview

NanoDB is a fully functional database engine built entirely with custom implementations of core data structures. The system manages memory, parses queries, optimizes joins and handles 100,000+ TPC-H benchmark records.

## 🏗️ Architecture

### Custom Data Structures (NO STL!)
- **Stack** - Expression parsing (infix to postfix conversion)
- **DataValue** - Polymorphic type system (int, float, string in same row)
- **Doubly Linked List** - O(1) LRU cache eviction
- **Buffer Pool** - Fixed-size memory manager with page eviction
- **HashMap** - O(1) system catalog lookups with chaining
- **AVL Tree** - Self-balancing index for O(log N) searches
- **Query Parser** - SQL WHERE clause parsing using Stack
- **Join Optimizer** - MST-based multi-table join optimization

## 🚀 Quick Start

### Prerequisites
- C++ compiler with C++17 support (g++ 7.0+)
- Git

### Compilation

```bash
# Clone the repository
git clone https://github.com/asmamalik0165/NanoDB-Architecture.git
cd NanoDB-Architecture

# Compile
g++ -std=c++17 -Iinclude -o bin/nanodb src/main.cpp src/DataValue.cpp src/BufferPool.cpp

# Run
./bin/nanodb
```

### Expected Output
## 📊 Performance Benchmarks

- **AVL Tree**: 10,000 insertions in 2ms, 0.194μs per search
- **Buffer Pool**: O(1) page access with LRU eviction
- **HashMap**: O(1) lookups with collision handling
- **Query Parser**: Handles complex nested expressions

## 🧪 Testing

Individual component tests:
```bash
./bin/test_stack       # Stack implementation
./bin/test_datavalue   # Polymorphic types
./bin/test_dll         # Doubly linked list
./bin/test_buffer      # Buffer pool with LRU
./bin/test_hashmap     # HashMap with collisions
./bin/test_avl         # AVL tree balancing
./bin/test_parser      # Query parser
./bin/test_optimizer   # Join optimizer
```

## 📁 Project Structure

## 📝 Execution Logs

All operations are logged to `logs/nanodb_execution.log`:

## 🎓 Course Information

- **Course**: CS-4002 Applied Programming
- **Institution**: FAST-NUCES Islamabad
- **Term**: MS-CS-Spring-2026

## ⚠️ Important Notes

- **NO STL containers used** - All data structures custom-built
- **Memory safe** - Valgrind tested for leaks
- **TPC-H compliant** - Uses industry-standard benchmark

## 📚 Key Algorithms Implemented

- Shunting Yard (infix to postfix)
- AVL rotations (tree balancing)
- Kruskal's MST (join optimization)
- LRU eviction (buffer management)
- Chaining (hash collision resolution)

## 🔗 Repository

https://github.com/asmamalik0165/NanoDB-Architecture

---

