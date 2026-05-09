#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include <string>
#include <sstream>
#include "Stack.h"

class QueryParser {
private:
    // Operator precedence (higher = higher priority)
    int precedence(const std::string& op) {
        if (op == "OR") return 1;
        if (op == "AND") return 2;
        if (op == "==" || op == "!=" || op == ">" || op == "<" || 
            op == ">=" || op == "<=") return 3;
        if (op == "+" || op == "-") return 4;
        if (op == "*" || op == "/" || op == "%") return 5;
        return 0;
    }
    
    bool isOperator(const std::string& token) {
        return token == "AND" || token == "OR" || 
               token == "==" || token == "!=" ||
               token == ">" || token == "<" || 
               token == ">=" || token == "<=" ||
               token == "+" || token == "-" ||
               token == "*" || token == "/" || token == "%";
    }
    
    bool isNumber(const std::string& token) {
        if (token.empty()) return false;
        size_t start = 0;
        if (token[0] == '-') start = 1;
        
        bool hasDecimal = false;
        for (size_t i = start; i < token.length(); i++) {
            if (token[i] == '.') {
                if (hasDecimal) return false;
                hasDecimal = true;
            } else if (!isdigit(token[i])) {
                return false;
            }
        }
        return true;
    }
    
public:
    // Tokenize input string
    void tokenize(const std::string& expression, std::string* tokens, int& count) {
        count = 0;
        std::string current = "";
        bool inString = false;
        
        for (size_t i = 0; i < expression.length(); i++) {
            char c = expression[i];
            
            // Handle string literals
            if (c == '"') {
                if (inString) {
                    tokens[count++] = current;
                    current = "";
                    inString = false;
                } else {
                    if (!current.empty()) {
                        tokens[count++] = current;
                        current = "";
                    }
                    inString = true;
                }
                continue;
            }
            
            if (inString) {
                current += c;
                continue;
            }
            
            // Handle parentheses
            if (c == '(' || c == ')') {
                if (!current.empty()) {
                    tokens[count++] = current;
                    current = "";
                }
                tokens[count++] = std::string(1, c);
                continue;
            }
            
            // Handle whitespace
            if (c == ' ' || c == '\t') {
                if (!current.empty()) {
                    tokens[count++] = current;
                    current = "";
                }
                continue;
            }
            
            // Handle operators (==, !=, >=, <=)
            if (c == '=' || c == '!' || c == '>' || c == '<') {
                if (!current.empty()) {
                    tokens[count++] = current;
                    current = "";
                }
                current += c;
                if (i + 1 < expression.length() && expression[i + 1] == '=') {
                    current += '=';
                    i++;
                }
                tokens[count++] = current;
                current = "";
                continue;
            }
            
            current += c;
        }
        
        if (!current.empty()) {
            tokens[count++] = current;
        }
    }
    
    // Convert infix to postfix (Shunting Yard Algorithm)
    std::string infixToPostfix(const std::string& infix) {
        std::string tokens[100];
        int tokenCount = 0;
        tokenize(infix, tokens, tokenCount);
        
        Stack<std::string> operatorStack(50);
        std::string postfix = "";
        
        for (int i = 0; i < tokenCount; i++) {
            std::string token = tokens[i];
            
            // Operand (number, variable, or string)
            if (!isOperator(token) && token != "(" && token != ")") {
                if (!postfix.empty()) postfix += " ";
                postfix += token;
            }
            // Left parenthesis
            else if (token == "(") {
                operatorStack.push(token);
            }
            // Right parenthesis
            else if (token == ")") {
                while (!operatorStack.isEmpty() && operatorStack.peek() != "(") {
                    postfix += " " + operatorStack.pop();
                }
                if (!operatorStack.isEmpty()) {
                    operatorStack.pop(); // Remove '('
                }
            }
            // Operator
            else if (isOperator(token)) {
                while (!operatorStack.isEmpty() && 
                       operatorStack.peek() != "(" &&
                       precedence(operatorStack.peek()) >= precedence(token)) {
                    postfix += " " + operatorStack.pop();
                }
                operatorStack.push(token);
            }
        }
        
        // Pop remaining operators
        while (!operatorStack.isEmpty()) {
            postfix += " " + operatorStack.pop();
        }
        
        return postfix;
    }
    
    // Evaluate postfix expression (simplified - returns true/false)
    bool evaluatePostfix(const std::string& postfix) {
        std::string tokens[100];
        int tokenCount = 0;
        
        // Tokenize postfix
        std::stringstream ss(postfix);
        std::string token;
        while (ss >> token) {
            tokens[tokenCount++] = token;
        }
        
        Stack<std::string> valueStack(50);
        
        for (int i = 0; i < tokenCount; i++) {
            std::string token = tokens[i];
            
            if (!isOperator(token)) {
                valueStack.push(token);
            } else {
                // Pop two operands
                std::string right = valueStack.pop();
                std::string left = valueStack.pop();
                
                // Evaluate (simplified - just for demo)
                bool result = false;
                
                if (token == ">") {
                    if (isNumber(left) && isNumber(right)) {
                        result = (std::stod(left) > std::stod(right));
                    }
                } else if (token == "<") {
                    if (isNumber(left) && isNumber(right)) {
                        result = (std::stod(left) < std::stod(right));
                    }
                } else if (token == "==") {
                    result = (left == right);
                } else if (token == "AND") {
                    result = (left == "true" && right == "true");
                } else if (token == "OR") {
                    result = (left == "true" || right == "true");
                }
                
                valueStack.push(result ? "true" : "false");
            }
        }
        
        return valueStack.peek() == "true";
    }
};

#endif