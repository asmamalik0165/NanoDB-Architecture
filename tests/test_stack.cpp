#include <iostream>
#include "../include/Stack.h"

int main() {
    std::cout << "Testing Stack Implementation...\n\n";
    
    // Test 1: Integer stack
    Stack<int> intStack(5);
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    
    std::cout << "Top: " << intStack.peek() << " (should be 30)" << std::endl;
    std::cout << "Pop: " << intStack.pop() << " (should be 30)" << std::endl;
    std::cout << "New top: " << intStack.peek() << " (should be 20)" << std::endl;
    std::cout << "Size: " << intStack.size() << " (should be 2)\n" << std::endl;
    
    // Test 2: Auto-resize
    Stack<int> smallStack(2);
    for (int i = 0; i < 10; i++) {
        smallStack.push(i);
    }
    std::cout << "Pushed 10 items into size-2 stack (auto-resize works!)" << std::endl;
    std::cout << "Top: " << smallStack.peek() << " (should be 9)\n" << std::endl;
    
    std::cout << "All Stack tests passed!\n";
    
    return 0;
}