#pragma once
#include <string>

// Abstract Product
class Product {
public:
    virtual ~Product() = default;
    virtual std::string getName() const = 0;
    virtual void use() const = 0;
};

// Concrete Product A
class ConcreteProductA : public Product {
public:
    std::string getName() const override {
        return "Product A";
    }
    
    void use() const override {
        // Product A specific implementation
    }
};

// Concrete Product B
class ConcreteProductB : public Product {
public:
    std::string getName() const override {
        return "Product B";
    }
    
    void use() const override {
        // Product B specific implementation
    }
};
