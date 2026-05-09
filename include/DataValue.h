#ifndef DATA_VALUE_H
#define DATA_VALUE_H

#include <string>
#include <cstring>

// Abstract base class
class DataValue {
public:
    virtual ~DataValue() {}
    virtual std::string toString() const = 0;
    virtual bool equals(const DataValue* other) const = 0;
    virtual bool lessThan(const DataValue* other) const = 0;
    virtual DataValue* clone() const = 0;
    
    virtual bool isInt() const { return false; }
    virtual bool isFloat() const { return false; }
    virtual bool isString() const { return false; }
};

// Integer type
class IntValue : public DataValue {
private:
    int value;
public:
    IntValue(int v) : value(v) {}
    int getValue() const { return value; }
    
    std::string toString() const override;
    bool equals(const DataValue* other) const override;
    bool lessThan(const DataValue* other) const override;
    DataValue* clone() const override { return new IntValue(value); }
    bool isInt() const override { return true; }
};

// Float type
class FloatValue : public DataValue {
private:
    float value;
public:
    FloatValue(float v) : value(v) {}
    float getValue() const { return value; }
    
    std::string toString() const override;
    bool equals(const DataValue* other) const override;
    bool lessThan(const DataValue* other) const override;
    DataValue* clone() const override { return new FloatValue(value); }
    bool isFloat() const override { return true; }
};

// String type (NO std::string allowed - using raw char*)
class StringValue : public DataValue {
private:
    char* value;
    size_t length;
public:
    StringValue(const char* v);
    ~StringValue();
    const char* getValue() const { return value; }
    
    std::string toString() const override;
    bool equals(const DataValue* other) const override;
    bool lessThan(const DataValue* other) const override;
    DataValue* clone() const override;
    bool isString() const override { return true; }
};

// Row - heterogeneous data container
class Row {
private:
    DataValue** columns;
    size_t numColumns;
public:
    Row(size_t cols);
    ~Row();
    
    void setColumn(size_t index, DataValue* value);
    DataValue* getColumn(size_t index) const;
    size_t getColumnCount() const { return numColumns; }
    std::string toString() const;
};

#endif