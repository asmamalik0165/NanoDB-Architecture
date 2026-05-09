#include "../include/DataValue.h"
#include <sstream>
#include <iomanip>

// IntValue implementation
std::string IntValue::toString() const {
    return std::to_string(value);
}

bool IntValue::equals(const DataValue* other) const {
    if (!other->isInt()) return false;
    return value == static_cast<const IntValue*>(other)->getValue();
}

bool IntValue::lessThan(const DataValue* other) const {
    if (!other->isInt()) return false;
    return value < static_cast<const IntValue*>(other)->getValue();
}

// FloatValue implementation
std::string FloatValue::toString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << value;
    return oss.str();
}

bool FloatValue::equals(const DataValue* other) const {
    if (!other->isFloat()) return false;
    return value == static_cast<const FloatValue*>(other)->getValue();
}

bool FloatValue::lessThan(const DataValue* other) const {
    if (!other->isFloat()) return false;
    return value < static_cast<const FloatValue*>(other)->getValue();
}

// StringValue implementation
StringValue::StringValue(const char* v) {
    length = strlen(v);
    value = new char[length + 1];
    strcpy(value, v);
}

StringValue::~StringValue() {
    delete[] value;
}

std::string StringValue::toString() const {
    return std::string(value);
}

bool StringValue::equals(const DataValue* other) const {
    if (!other->isString()) return false;
    return strcmp(value, static_cast<const StringValue*>(other)->getValue()) == 0;
}

bool StringValue::lessThan(const DataValue* other) const {
    if (!other->isString()) return false;
    return strcmp(value, static_cast<const StringValue*>(other)->getValue()) < 0;
}

DataValue* StringValue::clone() const {
    return new StringValue(value);
}

// Row implementation
Row::Row(size_t cols) : numColumns(cols) {
    columns = new DataValue*[numColumns];
    for (size_t i = 0; i < numColumns; i++) {
        columns[i] = nullptr;
    }
}

Row::~Row() {
    for (size_t i = 0; i < numColumns; i++) {
        if (columns[i] != nullptr) {
            delete columns[i];
        }
    }
    delete[] columns;
}

void Row::setColumn(size_t index, DataValue* value) {
    if (index >= numColumns) return;
    if (columns[index] != nullptr) {
        delete columns[index];
    }
    columns[index] = value;
}

DataValue* Row::getColumn(size_t index) const {
    if (index >= numColumns) return nullptr;
    return columns[index];
}

std::string Row::toString() const {
    std::string result = "[";
    for (size_t i = 0; i < numColumns; i++) {
        if (columns[i] != nullptr) {
            result += columns[i]->toString();
        } else {
            result += "NULL";
        }
        if (i < numColumns - 1) result += ", ";
    }
    result += "]";
    return result;
}