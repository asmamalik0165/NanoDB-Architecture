#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <algorithm>

template<typename K, typename V>
struct AVLNode {
    K key;
    V value;
    int height;
    AVLNode* left;
    AVLNode* right;
    
    AVLNode(const K& k, const V& v) 
        : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};

template<typename K, typename V>
class AVLTree {
private:
    AVLNode<K,V>* root;
    int nodeCount;
    
    // Get height of node
    int getHeight(AVLNode<K,V>* node) const {
        return node ? node->height : 0;
    }
    
    // Update height of node
    void updateHeight(AVLNode<K,V>* node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }
    
    // Get balance factor
    int getBalance(AVLNode<K,V>* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    // Right rotation
    AVLNode<K,V>* rotateRight(AVLNode<K,V>* y) {
        AVLNode<K,V>* x = y->left;
        AVLNode<K,V>* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    // Left rotation
    AVLNode<K,V>* rotateLeft(AVLNode<K,V>* x) {
        AVLNode<K,V>* y = x->right;
        AVLNode<K,V>* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    // Insert node (recursive)
    AVLNode<K,V>* insertNode(AVLNode<K,V>* node, const K& key, const V& value) {
        // Standard BST insertion
        if (node == nullptr) {
            nodeCount++;
            return new AVLNode<K,V>(key, value);
        }
        
        if (key < node->key) {
            node->left = insertNode(node->left, key, value);
        } else if (key > node->key) {
            node->right = insertNode(node->right, key, value);
        } else {
            // Key already exists - update value
            node->value = value;
            return node;
        }
        
        // Update height
        updateHeight(node);
        
        // Get balance factor
        int balance = getBalance(node);
        
        // Left-Left case
        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }
        
        // Right-Right case
        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }
        
        // Left-Right case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right-Left case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    // Search (recursive)
    AVLNode<K,V>* searchNode(AVLNode<K,V>* node, const K& key) {
        if (node == nullptr || node->key == key) {
            return node;
        }
        
        if (key < node->key) {
            return searchNode(node->left, key);
        } else {
            return searchNode(node->right, key);
        }
    }
    
    // In-order traversal
    void inorderTraversal(AVLNode<K,V>* node) {
        if (node) {
            inorderTraversal(node->left);
            std::cout << "(" << node->key << ":" << node->value << ") ";
            inorderTraversal(node->right);
        }
    }
    
    // Cleanup
    void destroyTree(AVLNode<K,V>* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
public:
    AVLTree() : root(nullptr), nodeCount(0) {}
    
    ~AVLTree() {
        destroyTree(root);
    }
    
    void insert(const K& key, const V& value) {
        root = insertNode(root, key, value);
    }
    
    V* search(const K& key) {
        AVLNode<K,V>* node = searchNode(root, key);
        return node ? &(node->value) : nullptr;
    }
    
    bool contains(const K& key) {
        return searchNode(root, key) != nullptr;
    }
    
    int size() const {
        return nodeCount;
    }
    
    int treeHeight() const {
        return getHeight(root);
    }
    
    void printInOrder() {
        inorderTraversal(root);
        std::cout << std::endl;
    }
    
    // Check if tree is balanced (for testing)
    bool isBalanced() {
        return checkBalance(root);
    }
    
private:
    bool checkBalance(AVLNode<K,V>* node) {
        if (node == nullptr) return true;
        
        int balance = getBalance(node);
        if (balance < -1 || balance > 1) return false;
        
        return checkBalance(node->left) && checkBalance(node->right);
    }
};

#endif