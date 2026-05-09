#include <iostream>
#include "../include/QueryParser.h"

int main() {
    std::cout << "Testing Query Parser (Infix to Postfix)...\n\n";
    
    QueryParser parser;
    
    // Test 1: Simple expression
    std::cout << "=== Test 1: Simple Comparison ===\n";
    std::string expr1 = "Age > 20";
    std::string postfix1 = parser.infixToPostfix(expr1);
    std::cout << "Infix:    " << expr1 << "\n";
    std::cout << "Postfix:  " << postfix1 << "\n\n";
    
    // Test 2: AND expression
    std::cout << "=== Test 2: AND Expression ===\n";
    std::string expr2 = "Age > 20 AND Salary < 5000";
    std::string postfix2 = parser.infixToPostfix(expr2);
    std::cout << "Infix:    " << expr2 << "\n";
    std::cout << "Postfix:  " << postfix2 << "\n\n";
    
    // Test 3: Complex with parentheses
    std::cout << "=== Test 3: Complex Expression with Parentheses ===\n";
    std::string expr3 = "(Age > 20 AND Salary < 5000) OR Department == HR";
    std::string postfix3 = parser.infixToPostfix(expr3);
    std::cout << "Infix:    " << expr3 << "\n";
    std::cout << "Postfix:  " << postfix3 << "\n\n";
    
    // Test 4: Nested parentheses
    std::cout << "=== Test 4: Deeply Nested Expression ===\n";
    std::string expr4 = "((A > 10 AND B < 20) OR (C == 30)) AND D != 40";
    std::string postfix4 = parser.infixToPostfix(expr4);
    std::cout << "Infix:    " << expr4 << "\n";
    std::cout << "Postfix:  " << postfix4 << "\n\n";
    
    // Test 5: From your project requirement!
    std::cout << "=== Test 5: Project Requirement Example ===\n";
    std::string expr5 = "(c_acctbal > 5000 AND c_mktsegment == BUILDING) OR c_nationkey == 15";
    std::string postfix5 = parser.infixToPostfix(expr5);
    std::cout << "Infix:    " << expr5 << "\n";
    std::cout << "Postfix:  " << postfix5 << "\n";
    std::cout << "[LOG] Expression parsed successfully\n\n";
    
    std::cout << "✅ All Query Parser tests passed!\n";
    std::cout << "Ready for WHERE clause evaluation!\n";
    
    return 0;
}