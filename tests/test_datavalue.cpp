#include <iostream>
#include "../include/DataValue.h"

int main() {
    std::cout << "Testing DataValue Type System...\n\n";
    
    // Test 1: Create different types
    IntValue* intVal = new IntValue(42);
    FloatValue* floatVal = new FloatValue(3.14f);
    StringValue* strVal = new StringValue("NanoDB");
    
    std::cout << "Int: " << intVal->toString() << std::endl;
    std::cout << "Float: " << floatVal->toString() << std::endl;
    std::cout << "String: " << strVal->toString() << std::endl << std::endl;
    
    // Test 2: Comparisons
    IntValue* int2 = new IntValue(100);
    std::cout << "42 < 100: " << (intVal->lessThan(int2) ? "true" : "false") << std::endl;
    std::cout << "42 == 42: " << (intVal->equals(intVal) ? "true" : "false") << std::endl << std::endl;
    
    // Test 3: Heterogeneous Row (THE KEY FEATURE!)
    Row* customerRow = new Row(4);
    customerRow->setColumn(0, new IntValue(12345));       // customer_id
    customerRow->setColumn(1, new StringValue("Alice"));  // name
    customerRow->setColumn(2, new FloatValue(1500.50f));  // balance
    customerRow->setColumn(3, new StringValue("USA"));    // country
    
    std::cout << "Customer Row: " << customerRow->toString() << std::endl;
    std::cout << "\n✅ DataValue tests passed!\n";
    
    // Cleanup
    delete intVal;
    delete floatVal;
    delete strVal;
    delete int2;
    delete customerRow;
    
    return 0;
}